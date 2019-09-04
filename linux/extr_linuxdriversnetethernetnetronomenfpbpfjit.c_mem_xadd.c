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
typedef  int u8 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct TYPE_2__ {int dst_reg; int src_reg; scalar_t__ off; } ;
struct nfp_insn_meta {scalar_t__ xadd_over_16bit; scalar_t__ xadd_maybe_16bit; TYPE_1__ insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_ADD ; 
 int /*<<< orphan*/  ALU_OP_ADD_C ; 
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  ALU_OP_SUB_C ; 
 int /*<<< orphan*/  BR_BLO ; 
 int /*<<< orphan*/  BR_UNC ; 
 int /*<<< orphan*/  CMD_CTX_NO_SWAP ; 
 int /*<<< orphan*/  CMD_CTX_SWAP_DEFER1 ; 
 int /*<<< orphan*/  CMD_CTX_SWAP_DEFER2 ; 
 int /*<<< orphan*/  CMD_MODE_40b_BA ; 
 int /*<<< orphan*/  CMD_OVE_DATA ; 
 int CMD_OVE_LEN ; 
 int /*<<< orphan*/  CMD_OV_LEN ; 
 int /*<<< orphan*/  CMD_TGT_ADD ; 
 int /*<<< orphan*/  CMD_TGT_ADD_IMM ; 
 int EINVAL ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  emit_cmd (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_cmd_indir (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  imma_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  imma_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_prog_confirm_current_offset (struct nfp_prog*,unsigned int) ; 
 unsigned int nfp_prog_current_offset (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  reg_xfer (int) ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_reg_or_subpart (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
mem_xadd(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta, bool is64)
{
	u8 dst_gpr = meta->insn.dst_reg * 2;
	u8 src_gpr = meta->insn.src_reg * 2;
	unsigned int full_add, out;
	swreg addra, addrb, off;

	off = ur_load_imm_any(nfp_prog, meta->insn.off, imm_b(nfp_prog));

	/* We can fit 16 bits into command immediate, if we know the immediate
	 * is guaranteed to either always or never fit into 16 bit we only
	 * generate code to handle that particular case, otherwise generate
	 * code for both.
	 */
	out = nfp_prog_current_offset(nfp_prog);
	full_add = nfp_prog_current_offset(nfp_prog);

	if (meta->insn.off) {
		out += 2;
		full_add += 2;
	}
	if (meta->xadd_maybe_16bit) {
		out += 3;
		full_add += 3;
	}
	if (meta->xadd_over_16bit)
		out += 2 + is64;
	if (meta->xadd_maybe_16bit && meta->xadd_over_16bit) {
		out += 5;
		full_add += 5;
	}

	/* Generate the branch for choosing add_imm vs add */
	if (meta->xadd_maybe_16bit && meta->xadd_over_16bit) {
		swreg max_imm = imm_a(nfp_prog);

		wrp_immed(nfp_prog, max_imm, 0xffff);
		emit_alu(nfp_prog, reg_none(),
			 max_imm, ALU_OP_SUB, reg_b(src_gpr));
		emit_alu(nfp_prog, reg_none(),
			 reg_imm(0), ALU_OP_SUB_C, reg_b(src_gpr + 1));
		emit_br(nfp_prog, BR_BLO, full_add, meta->insn.off ? 2 : 0);
		/* defer for add */
	}

	/* If insn has an offset add to the address */
	if (!meta->insn.off) {
		addra = reg_a(dst_gpr);
		addrb = reg_b(dst_gpr + 1);
	} else {
		emit_alu(nfp_prog, imma_a(nfp_prog),
			 reg_a(dst_gpr), ALU_OP_ADD, off);
		emit_alu(nfp_prog, imma_b(nfp_prog),
			 reg_a(dst_gpr + 1), ALU_OP_ADD_C, reg_imm(0));
		addra = imma_a(nfp_prog);
		addrb = imma_b(nfp_prog);
	}

	/* Generate the add_imm if 16 bits are possible */
	if (meta->xadd_maybe_16bit) {
		swreg prev_alu = imm_a(nfp_prog);

		wrp_immed(nfp_prog, prev_alu,
			  FIELD_PREP(CMD_OVE_DATA, 2) |
			  CMD_OVE_LEN |
			  FIELD_PREP(CMD_OV_LEN, 0x8 | is64 << 2));
		wrp_reg_or_subpart(nfp_prog, prev_alu, reg_b(src_gpr), 2, 2);
		emit_cmd_indir(nfp_prog, CMD_TGT_ADD_IMM, CMD_MODE_40b_BA, 0,
			       addra, addrb, 0, CMD_CTX_NO_SWAP);

		if (meta->xadd_over_16bit)
			emit_br(nfp_prog, BR_UNC, out, 0);
	}

	if (!nfp_prog_confirm_current_offset(nfp_prog, full_add))
		return -EINVAL;

	/* Generate the add if 16 bits are not guaranteed */
	if (meta->xadd_over_16bit) {
		emit_cmd(nfp_prog, CMD_TGT_ADD, CMD_MODE_40b_BA, 0,
			 addra, addrb, is64 << 2,
			 is64 ? CMD_CTX_SWAP_DEFER2 : CMD_CTX_SWAP_DEFER1);

		wrp_mov(nfp_prog, reg_xfer(0), reg_a(src_gpr));
		if (is64)
			wrp_mov(nfp_prog, reg_xfer(1), reg_a(src_gpr + 1));
	}

	if (!nfp_prog_confirm_current_offset(nfp_prog, out))
		return -EINVAL;

	return 0;
}