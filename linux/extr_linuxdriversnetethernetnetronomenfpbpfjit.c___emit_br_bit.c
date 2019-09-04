#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int,int) ; 
 int OP_BR_BIT_ADDR_HI ; 
 int OP_BR_BIT_ADDR_LO ; 
 int OP_BR_BIT_A_SRC ; 
 int OP_BR_BIT_BASE ; 
 int OP_BR_BIT_BV ; 
 int OP_BR_BIT_B_SRC ; 
 int OP_BR_BIT_DEFBR ; 
 int OP_BR_BIT_SRC_LMEXTN ; 
 int __bf_shf (int) ; 
 int /*<<< orphan*/  nfp_prog_push (struct nfp_prog*,int) ; 

__attribute__((used)) static void
__emit_br_bit(struct nfp_prog *nfp_prog, u16 areg, u16 breg, u16 addr, u8 defer,
	      bool set, bool src_lmextn)
{
	u16 addr_lo, addr_hi;
	u64 insn;

	addr_lo = addr & (OP_BR_BIT_ADDR_LO >> __bf_shf(OP_BR_BIT_ADDR_LO));
	addr_hi = addr != addr_lo;

	insn = OP_BR_BIT_BASE |
		FIELD_PREP(OP_BR_BIT_A_SRC, areg) |
		FIELD_PREP(OP_BR_BIT_B_SRC, breg) |
		FIELD_PREP(OP_BR_BIT_BV, set) |
		FIELD_PREP(OP_BR_BIT_DEFBR, defer) |
		FIELD_PREP(OP_BR_BIT_ADDR_LO, addr_lo) |
		FIELD_PREP(OP_BR_BIT_ADDR_HI, addr_hi) |
		FIELD_PREP(OP_BR_BIT_SRC_LMEXTN, src_lmextn);

	nfp_prog_push(nfp_prog, insn);
}