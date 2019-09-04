#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {scalar_t__ adjust_head_location; TYPE_1__* bpf; } ;
struct nfp_insn_meta {scalar_t__ n; } ;
struct nfp_bpf_cap_adjust_head {int /*<<< orphan*/  off_max; int /*<<< orphan*/  off_min; } ;
struct TYPE_2__ {struct nfp_bpf_cap_adjust_head adjust_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_ADD ; 
 int /*<<< orphan*/  ALU_OP_ADD_2B ; 
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  BR_BLO ; 
 int /*<<< orphan*/  BR_BMI ; 
 int /*<<< orphan*/  BR_UNC ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  SHF_SC_NONE ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  emit_ld_field (struct nfp_prog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_prog_confirm_current_offset (struct nfp_prog*,scalar_t__) ; 
 scalar_t__ nfp_prog_current_offset (struct nfp_prog*) ; 
 int /*<<< orphan*/  plen_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  pptr_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  pv_len (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adjust_head(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	swreg tmp = imm_a(nfp_prog), tmp_len = imm_b(nfp_prog);
	struct nfp_bpf_cap_adjust_head *adjust_head;
	u32 ret_einval, end;

	adjust_head = &nfp_prog->bpf->adjust_head;

	/* Optimized version - 5 vs 14 cycles */
	if (nfp_prog->adjust_head_location != UINT_MAX) {
		if (WARN_ON_ONCE(nfp_prog->adjust_head_location != meta->n))
			return -EINVAL;

		emit_alu(nfp_prog, pptr_reg(nfp_prog),
			 reg_a(2 * 2), ALU_OP_ADD, pptr_reg(nfp_prog));
		emit_alu(nfp_prog, plen_reg(nfp_prog),
			 plen_reg(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));
		emit_alu(nfp_prog, pv_len(nfp_prog),
			 pv_len(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));

		wrp_immed(nfp_prog, reg_both(0), 0);
		wrp_immed(nfp_prog, reg_both(1), 0);

		/* TODO: when adjust head is guaranteed to succeed we can
		 * also eliminate the following if (r0 == 0) branch.
		 */

		return 0;
	}

	ret_einval = nfp_prog_current_offset(nfp_prog) + 14;
	end = ret_einval + 2;

	/* We need to use a temp because offset is just a part of the pkt ptr */
	emit_alu(nfp_prog, tmp,
		 reg_a(2 * 2), ALU_OP_ADD_2B, pptr_reg(nfp_prog));

	/* Validate result will fit within FW datapath constraints */
	emit_alu(nfp_prog, reg_none(),
		 tmp, ALU_OP_SUB, reg_imm(adjust_head->off_min));
	emit_br(nfp_prog, BR_BLO, ret_einval, 0);
	emit_alu(nfp_prog, reg_none(),
		 reg_imm(adjust_head->off_max), ALU_OP_SUB, tmp);
	emit_br(nfp_prog, BR_BLO, ret_einval, 0);

	/* Validate the length is at least ETH_HLEN */
	emit_alu(nfp_prog, tmp_len,
		 plen_reg(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));
	emit_alu(nfp_prog, reg_none(),
		 tmp_len, ALU_OP_SUB, reg_imm(ETH_HLEN));
	emit_br(nfp_prog, BR_BMI, ret_einval, 0);

	/* Load the ret code */
	wrp_immed(nfp_prog, reg_both(0), 0);
	wrp_immed(nfp_prog, reg_both(1), 0);

	/* Modify the packet metadata */
	emit_ld_field(nfp_prog, pptr_reg(nfp_prog), 0x3, tmp, SHF_SC_NONE, 0);

	/* Skip over the -EINVAL ret code (defer 2) */
	emit_br(nfp_prog, BR_UNC, end, 2);

	emit_alu(nfp_prog, plen_reg(nfp_prog),
		 plen_reg(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));
	emit_alu(nfp_prog, pv_len(nfp_prog),
		 pv_len(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));

	/* return -EINVAL target */
	if (!nfp_prog_confirm_current_offset(nfp_prog, ret_einval))
		return -EINVAL;

	wrp_immed(nfp_prog, reg_both(0), -22);
	wrp_immed(nfp_prog, reg_both(1), ~0);

	if (!nfp_prog_confirm_current_offset(nfp_prog, end))
		return -EINVAL;

	return 0;
}