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
typedef  enum br_mask { ____Placeholder_br_mask } br_mask ;
typedef  enum br_ev_pip { ____Placeholder_br_ev_pip } br_ev_pip ;
typedef  enum br_ctx_signal_state { ____Placeholder_br_ctx_signal_state } br_ctx_signal_state ;

/* Variables and functions */
 int FIELD_PREP (int,int) ; 
 int OP_BR_ADDR_HI ; 
 int OP_BR_ADDR_LO ; 
 int OP_BR_BASE ; 
 int OP_BR_CSS ; 
 int OP_BR_DEFBR ; 
 int OP_BR_EV_PIP ; 
 int OP_BR_MASK ; 
 int __bf_shf (int) ; 
 int /*<<< orphan*/  nfp_prog_push (struct nfp_prog*,int) ; 

__attribute__((used)) static void
__emit_br(struct nfp_prog *nfp_prog, enum br_mask mask, enum br_ev_pip ev_pip,
	  enum br_ctx_signal_state css, u16 addr, u8 defer)
{
	u16 addr_lo, addr_hi;
	u64 insn;

	addr_lo = addr & (OP_BR_ADDR_LO >> __bf_shf(OP_BR_ADDR_LO));
	addr_hi = addr != addr_lo;

	insn = OP_BR_BASE |
		FIELD_PREP(OP_BR_MASK, mask) |
		FIELD_PREP(OP_BR_EV_PIP, ev_pip) |
		FIELD_PREP(OP_BR_CSS, css) |
		FIELD_PREP(OP_BR_DEFBR, defer) |
		FIELD_PREP(OP_BR_ADDR_LO, addr_lo) |
		FIELD_PREP(OP_BR_ADDR_HI, addr_hi);

	nfp_prog_push(nfp_prog, insn);
}