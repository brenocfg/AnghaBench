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

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_OR ; 
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  SHF_OP_NONE ; 
 int /*<<< orphan*/  SHF_SC_R_DSHF ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_shf_indir (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  imm_both (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (scalar_t__) ; 
 int /*<<< orphan*/  reg_b (scalar_t__) ; 
 int /*<<< orphan*/  reg_both (scalar_t__) ; 
 int /*<<< orphan*/  reg_imm (int) ; 
 int /*<<< orphan*/  reg_none () ; 

__attribute__((used)) static void shl_reg64_lt32_high(struct nfp_prog *nfp_prog, u8 dst, u8 src)
{
	emit_alu(nfp_prog, imm_both(nfp_prog), reg_imm(32), ALU_OP_SUB,
		 reg_b(src));
	emit_alu(nfp_prog, reg_none(), imm_a(nfp_prog), ALU_OP_OR, reg_imm(0));
	emit_shf_indir(nfp_prog, reg_both(dst + 1), reg_a(dst + 1), SHF_OP_NONE,
		       reg_b(dst), SHF_SC_R_DSHF);
}