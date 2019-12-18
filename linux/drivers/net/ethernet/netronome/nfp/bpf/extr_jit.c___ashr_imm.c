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
typedef  scalar_t__ u8 ;
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_OR ; 
 int /*<<< orphan*/  SHF_OP_ASHR ; 
 int /*<<< orphan*/  SHF_SC_R_SHF ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  reg_a (scalar_t__) ; 
 int /*<<< orphan*/  reg_b (scalar_t__) ; 
 int /*<<< orphan*/  reg_both (scalar_t__) ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  wrp_zext (struct nfp_prog*,struct nfp_insn_meta*,scalar_t__) ; 

__attribute__((used)) static int
__ashr_imm(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta, u8 dst,
	   u8 shift_amt)
{
	if (shift_amt) {
		/* Set signedness bit (MSB of result). */
		emit_alu(nfp_prog, reg_none(), reg_a(dst), ALU_OP_OR,
			 reg_imm(0));
		emit_shf(nfp_prog, reg_both(dst), reg_none(), SHF_OP_ASHR,
			 reg_b(dst), SHF_SC_R_SHF, shift_amt);
	}
	wrp_zext(nfp_prog, meta, dst);

	return 0;
}