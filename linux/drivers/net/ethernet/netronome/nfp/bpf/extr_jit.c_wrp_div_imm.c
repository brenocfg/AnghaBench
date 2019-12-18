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
typedef  unsigned int u8 ;
typedef  unsigned int u64 ;
typedef  int /*<<< orphan*/  swreg ;
struct reciprocal_value_adv {unsigned int exp; unsigned int m; int sh; scalar_t__ is_wide_m; } ;
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_ADD ; 
 int /*<<< orphan*/  ALU_OP_ADD_C ; 
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  SHF_OP_NONE ; 
 int /*<<< orphan*/  SHF_SC_R_SHF ; 
 unsigned int U32_MAX ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int fls (unsigned int) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  imm_both (struct nfp_prog*) ; 
 struct reciprocal_value_adv reciprocal_value_adv (unsigned int,int) ; 
 int /*<<< orphan*/  reg_a (unsigned int) ; 
 int /*<<< orphan*/  reg_both (unsigned int) ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_mul_u32 (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wrp_div_imm(struct nfp_prog *nfp_prog, u8 dst, u64 imm)
{
	swreg dst_both = reg_both(dst), dst_a = reg_a(dst), dst_b = reg_a(dst);
	struct reciprocal_value_adv rvalue;
	u8 pre_shift, exp;
	swreg magic;

	if (imm > U32_MAX) {
		wrp_immed(nfp_prog, dst_both, 0);
		return 0;
	}

	/* NOTE: because we are using "reciprocal_value_adv" which doesn't
	 * support "divisor > (1u << 31)", we need to JIT separate NFP sequence
	 * to handle such case which actually equals to the result of unsigned
	 * comparison "dst >= imm" which could be calculated using the following
	 * NFP sequence:
	 *
	 *  alu[--, dst, -, imm]
	 *  immed[imm, 0]
	 *  alu[dst, imm, +carry, 0]
	 *
	 */
	if (imm > 1U << 31) {
		swreg tmp_b = ur_load_imm_any(nfp_prog, imm, imm_b(nfp_prog));

		emit_alu(nfp_prog, reg_none(), dst_a, ALU_OP_SUB, tmp_b);
		wrp_immed(nfp_prog, imm_a(nfp_prog), 0);
		emit_alu(nfp_prog, dst_both, imm_a(nfp_prog), ALU_OP_ADD_C,
			 reg_imm(0));
		return 0;
	}

	rvalue = reciprocal_value_adv(imm, 32);
	exp = rvalue.exp;
	if (rvalue.is_wide_m && !(imm & 1)) {
		pre_shift = fls(imm & -imm) - 1;
		rvalue = reciprocal_value_adv(imm >> pre_shift, 32 - pre_shift);
	} else {
		pre_shift = 0;
	}
	magic = ur_load_imm_any(nfp_prog, rvalue.m, imm_b(nfp_prog));
	if (imm == 1U << exp) {
		emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE, dst_b,
			 SHF_SC_R_SHF, exp);
	} else if (rvalue.is_wide_m) {
		wrp_mul_u32(nfp_prog, imm_both(nfp_prog), reg_none(), dst_a,
			    magic, true);
		emit_alu(nfp_prog, dst_both, dst_a, ALU_OP_SUB,
			 imm_b(nfp_prog));
		emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE, dst_b,
			 SHF_SC_R_SHF, 1);
		emit_alu(nfp_prog, dst_both, dst_a, ALU_OP_ADD,
			 imm_b(nfp_prog));
		emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE, dst_b,
			 SHF_SC_R_SHF, rvalue.sh - 1);
	} else {
		if (pre_shift)
			emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE,
				 dst_b, SHF_SC_R_SHF, pre_shift);
		wrp_mul_u32(nfp_prog, dst_both, reg_none(), dst_a, magic, true);
		emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE,
			 dst_b, SHF_SC_R_SHF, rvalue.sh);
	}

	return 0;
}