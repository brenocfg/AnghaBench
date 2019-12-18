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
 int /*<<< orphan*/  SHF_OP_ASHR ; 
 int /*<<< orphan*/  SHF_SC_R_SHF ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_shf_indir (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_a (scalar_t__) ; 
 int /*<<< orphan*/  reg_b (scalar_t__) ; 
 int /*<<< orphan*/  reg_both (scalar_t__) ; 
 int /*<<< orphan*/  reg_none () ; 

__attribute__((used)) static void ashr_reg64_ge32(struct nfp_prog *nfp_prog, u8 dst, u8 src)
{
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_b(dst + 1));
	emit_shf_indir(nfp_prog, reg_both(dst), reg_none(), SHF_OP_ASHR,
		       reg_b(dst + 1), SHF_SC_R_SHF);
	emit_shf(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_ASHR,
		 reg_b(dst + 1), SHF_SC_R_SHF, 31);
}