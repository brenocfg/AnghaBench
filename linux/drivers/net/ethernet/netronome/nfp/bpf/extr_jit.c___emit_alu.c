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
typedef  enum alu_op { ____Placeholder_alu_op } alu_op ;
typedef  enum alu_dst_ab { ____Placeholder_alu_dst_ab } alu_dst_ab ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OP_ALU_A_SRC ; 
 int OP_ALU_BASE ; 
 int /*<<< orphan*/  OP_ALU_B_SRC ; 
 int /*<<< orphan*/  OP_ALU_DST ; 
 int /*<<< orphan*/  OP_ALU_DST_AB ; 
 int /*<<< orphan*/  OP_ALU_DST_LMEXTN ; 
 int /*<<< orphan*/  OP_ALU_OP ; 
 int /*<<< orphan*/  OP_ALU_SRC_LMEXTN ; 
 int /*<<< orphan*/  OP_ALU_SW ; 
 int /*<<< orphan*/  OP_ALU_WR_AB ; 
 int /*<<< orphan*/  nfp_prog_push (struct nfp_prog*,int) ; 

__attribute__((used)) static void
__emit_alu(struct nfp_prog *nfp_prog, u16 dst, enum alu_dst_ab dst_ab,
	   u16 areg, enum alu_op op, u16 breg, bool swap, bool wr_both,
	   bool dst_lmextn, bool src_lmextn)
{
	u64 insn;

	insn = OP_ALU_BASE |
		FIELD_PREP(OP_ALU_A_SRC, areg) |
		FIELD_PREP(OP_ALU_B_SRC, breg) |
		FIELD_PREP(OP_ALU_DST, dst) |
		FIELD_PREP(OP_ALU_SW, swap) |
		FIELD_PREP(OP_ALU_OP, op) |
		FIELD_PREP(OP_ALU_DST_AB, dst_ab) |
		FIELD_PREP(OP_ALU_WR_AB, wr_both) |
		FIELD_PREP(OP_ALU_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_ALU_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
}