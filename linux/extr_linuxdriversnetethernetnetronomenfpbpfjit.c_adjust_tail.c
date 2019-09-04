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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ swreg ;
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_ADD ; 
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  BR_BCC ; 
 int /*<<< orphan*/  BR_BMI ; 
 int /*<<< orphan*/  BR_UNC ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  STATIC_REG_PKT_LEN ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_prog_confirm_current_offset (struct nfp_prog*,scalar_t__) ; 
 scalar_t__ nfp_prog_current_offset (struct nfp_prog*) ; 
 scalar_t__ plen_reg (struct nfp_prog*) ; 
 scalar_t__ pv_len (struct nfp_prog*) ; 
 scalar_t__ reg_a (int) ; 
 scalar_t__ reg_b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 scalar_t__ reg_imm (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_none () ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adjust_tail(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	u32 ret_einval, end;
	swreg plen, delta;

	BUILD_BUG_ON(plen_reg(nfp_prog) != reg_b(STATIC_REG_PKT_LEN));

	plen = imm_a(nfp_prog);
	delta = reg_a(2 * 2);

	ret_einval = nfp_prog_current_offset(nfp_prog) + 9;
	end = nfp_prog_current_offset(nfp_prog) + 11;

	/* Calculate resulting length */
	emit_alu(nfp_prog, plen, plen_reg(nfp_prog), ALU_OP_ADD, delta);
	/* delta == 0 is not allowed by the kernel, add must overflow to make
	 * length smaller.
	 */
	emit_br(nfp_prog, BR_BCC, ret_einval, 0);

	/* if (new_len < 14) then -EINVAL */
	emit_alu(nfp_prog, reg_none(), plen, ALU_OP_SUB, reg_imm(ETH_HLEN));
	emit_br(nfp_prog, BR_BMI, ret_einval, 0);

	emit_alu(nfp_prog, plen_reg(nfp_prog),
		 plen_reg(nfp_prog), ALU_OP_ADD, delta);
	emit_alu(nfp_prog, pv_len(nfp_prog),
		 pv_len(nfp_prog), ALU_OP_ADD, delta);

	emit_br(nfp_prog, BR_UNC, end, 2);
	wrp_immed(nfp_prog, reg_both(0), 0);
	wrp_immed(nfp_prog, reg_both(1), 0);

	if (!nfp_prog_confirm_current_offset(nfp_prog, ret_einval))
		return -EINVAL;

	wrp_immed(nfp_prog, reg_both(0), -22);
	wrp_immed(nfp_prog, reg_both(1), ~0);

	if (!nfp_prog_confirm_current_offset(nfp_prog, end))
		return -EINVAL;

	return 0;
}