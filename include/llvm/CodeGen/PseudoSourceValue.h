//===-- llvm/CodeGen/PseudoSourceValue.h ------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the PseudoSourceValue class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CODEGEN_PSEUDOSOURCEVALUE_H
#define LLVM_CODEGEN_PSEUDOSOURCEVALUE_H

#include "llvm/Value.h"

namespace llvm {
  class MachineFrameInfo;
  class raw_ostream;

  /// PseudoSourceValue - Special value supplied for machine level alias
  /// analysis. It indicates that the a memory access references the functions
  /// stack frame (e.g., a spill slot), below the stack frame (e.g., argument
  /// space), or constant pool.
  class PseudoSourceValue : public Value {
  private:
    /// printCustom - Implement printing for PseudoSourceValue. This is called
    /// from Value::print or Value's operator<<.
    ///
    virtual void printCustom(raw_ostream &O) const;

  public:
    PseudoSourceValue();

    /// isConstant - Test whether the memory pointed to by this
    /// PseudoSourceValue has a constant value.
    ///
    virtual bool isConstant(const MachineFrameInfo *) const;

    /// classof - Methods for support type inquiry through isa, cast, and
    /// dyn_cast:
    ///
    static inline bool classof(const PseudoSourceValue *) { return true; }
    static inline bool classof(const Value *V) {
      return V->getValueID() == PseudoSourceValueVal;
    }

    /// A pseudo source value referencing a stack frame entry,
    /// e.g., a spill slot or an incoming argument on stack.
    static const PseudoSourceValue *getStackObject(int FI);

    /// A pseudo source value referencing the area below the stack frame of
    /// a function, e.g., the argument space.
    static const PseudoSourceValue *getStack();

    /// A pseudo source value referencing the global offset table
    /// (or something the like).
    static const PseudoSourceValue *getGOT();

    /// A pseudo source value referencing the constant pool. Since constant
    /// pools are constant, this doesn't need to identify a specific constant
    /// pool entry.
    static const PseudoSourceValue *getConstantPool();

    /// A pseudo source value referencing a jump table. Since jump tables are
    /// constant, this doesn't need to identify a specific jump table.
    static const PseudoSourceValue *getJumpTable();
  };
} // End llvm namespace

#endif
