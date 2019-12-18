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
struct nfp_prog {int /*<<< orphan*/  error; } ;
typedef  enum shf_sc { ____Placeholder_shf_sc } shf_sc ;
typedef  enum shf_op { ____Placeholder_shf_op } shf_op ;
typedef  enum alu_dst_ab { ____Placeholder_alu_dst_ab } alu_dst_ab ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  FIELD_FIT (int /*<<< orphan*/ ,int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OP_SHF_A_SRC ; 
 int OP_SHF_BASE ; 
 int /*<<< orphan*/  OP_SHF_B_SRC ; 
 int /*<<< orphan*/  OP_SHF_DST ; 
 int /*<<< orphan*/  OP_SHF_DST_AB ; 
 int /*<<< orphan*/  OP_SHF_DST_LMEXTN ; 
 int /*<<< orphan*/  OP_SHF_I8 ; 
 int /*<<< orphan*/  OP_SHF_OP ; 
 int /*<<< orphan*/  OP_SHF_SC ; 
 int /*<<< orphan*/  OP_SHF_SHIFT ; 
 int /*<<< orphan*/  OP_SHF_SRC_LMEXTN ; 
 int /*<<< orphan*/  OP_SHF_SW ; 
 int /*<<< orphan*/  OP_SHF_WR_AB ; 
 int SHF_SC_L_SHF ; 
 int /*<<< orphan*/  nfp_prog_push (struct nfp_prog*,int) ; 

__attribute__((used)) static void
__emit_shf(struct nfp_prog *nfp_prog, u16 dst, enum alu_dst_ab dst_ab,
	   enum shf_sc sc, u8 shift,
	   u16 areg, enum shf_op op, u16 breg, bool i8, bool sw, bool wr_both,
	   bool dst_lmextn, bool src_lmextn)
{
	u64 insn;

	if (!FIELD_FIT(OP_SHF_SHIFT, shift)) {
		nfp_prog->error = -EFAULT;
		return;
	}

	/* NFP shift instruction has something special. If shift direction is
	 * left then shift amount of 1 to 31 is specified as 32 minus the amount
	 * to shift.
	 *
	 * But no need to do this for indirect shift which has shift amount be
	 * 0. Even after we do this subtraction, shift amount 0 will be turned
	 * into 32 which will eventually be encoded the same as 0 because only
	 * low 5 bits are encoded, but shift amount be 32 will fail the
	 * FIELD_PREP check done later on shift mask (0x1f), due to 32 is out of
	 * mask range.
	 */
	if (sc == SHF_SC_L_SHF && shift)
		shift = 32 - shift;

	insn = OP_SHF_BASE |
		FIELD_PREP(OP_SHF_A_SRC, areg) |
		FIELD_PREP(OP_SHF_SC, sc) |
		FIELD_PREP(OP_SHF_B_SRC, breg) |
		FIELD_PREP(OP_SHF_I8, i8) |
		FIELD_PREP(OP_SHF_SW, sw) |
		FIELD_PREP(OP_SHF_DST, dst) |
		FIELD_PREP(OP_SHF_SHIFT, shift) |
		FIELD_PREP(OP_SHF_OP, op) |
		FIELD_PREP(OP_SHF_DST_AB, dst_ab) |
		FIELD_PREP(OP_SHF_WR_AB, wr_both) |
		FIELD_PREP(OP_SHF_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_SHF_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
}