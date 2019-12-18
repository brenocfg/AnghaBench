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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct bpf_insn {int dst_reg; int src_reg; scalar_t__ imm; } ;
struct nfp_insn_meta {scalar_t__ umax_dst; scalar_t__ umax_src; struct bpf_insn insn; } ;

/* Variables and functions */
 scalar_t__ U16_MAX ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_mul_u16 (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_mul_u32 (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
wrp_mul(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
	bool gen_high_half, bool ropnd_from_reg)
{
	swreg multiplier, multiplicand, dst_hi, dst_lo;
	const struct bpf_insn *insn = &meta->insn;
	u32 lopnd_max, ropnd_max;
	u8 dst_reg;

	dst_reg = insn->dst_reg;
	multiplicand = reg_a(dst_reg * 2);
	dst_hi = reg_both(dst_reg * 2 + 1);
	dst_lo = reg_both(dst_reg * 2);
	lopnd_max = meta->umax_dst;
	if (ropnd_from_reg) {
		multiplier = reg_b(insn->src_reg * 2);
		ropnd_max = meta->umax_src;
	} else {
		u32 imm = insn->imm;

		multiplier = ur_load_imm_any(nfp_prog, imm, imm_b(nfp_prog));
		ropnd_max = imm;
	}
	if (lopnd_max > U16_MAX || ropnd_max > U16_MAX)
		wrp_mul_u32(nfp_prog, dst_hi, dst_lo, multiplicand, multiplier,
			    gen_high_half);
	else
		wrp_mul_u16(nfp_prog, dst_hi, dst_lo, multiplicand, multiplier);

	return 0;
}