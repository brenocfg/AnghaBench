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
typedef  int u64 ;
typedef  int u16 ;
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OP_LCSR_ADDR ; 
 int /*<<< orphan*/  OP_LCSR_A_SRC ; 
 int OP_LCSR_BASE ; 
 int /*<<< orphan*/  OP_LCSR_B_SRC ; 
 int /*<<< orphan*/  OP_LCSR_DST_LMEXTN ; 
 int /*<<< orphan*/  OP_LCSR_SRC_LMEXTN ; 
 int /*<<< orphan*/  OP_LCSR_WRITE ; 
 int /*<<< orphan*/  nfp_prog_push (struct nfp_prog*,int) ; 

__attribute__((used)) static void
__emit_lcsr(struct nfp_prog *nfp_prog, u16 areg, u16 breg, bool wr, u16 addr,
	    bool dst_lmextn, bool src_lmextn)
{
	u64 insn;

	insn = OP_LCSR_BASE |
		FIELD_PREP(OP_LCSR_A_SRC, areg) |
		FIELD_PREP(OP_LCSR_B_SRC, breg) |
		FIELD_PREP(OP_LCSR_WRITE, wr) |
		FIELD_PREP(OP_LCSR_ADDR, addr / 4) |
		FIELD_PREP(OP_LCSR_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_LCSR_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
}