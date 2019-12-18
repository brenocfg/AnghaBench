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
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHF_OP_NONE ; 
 int /*<<< orphan*/  SHF_SC_R_DSHF ; 
 int /*<<< orphan*/  SHF_SC_R_SHF ; 
 int /*<<< orphan*/  emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_reg_mov (struct nfp_prog*,int,int) ; 

__attribute__((used)) static int __shr_imm64(struct nfp_prog *nfp_prog, u8 dst, u8 shift_amt)
{
	if (!shift_amt)
		return 0;

	if (shift_amt < 32) {
		emit_shf(nfp_prog, reg_both(dst), reg_a(dst + 1), SHF_OP_NONE,
			 reg_b(dst), SHF_SC_R_DSHF, shift_amt);
		emit_shf(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_NONE,
			 reg_b(dst + 1), SHF_SC_R_SHF, shift_amt);
	} else if (shift_amt == 32) {
		wrp_reg_mov(nfp_prog, dst, dst + 1);
		wrp_immed(nfp_prog, reg_both(dst + 1), 0);
	} else if (shift_amt > 32) {
		emit_shf(nfp_prog, reg_both(dst), reg_none(), SHF_OP_NONE,
			 reg_b(dst + 1), SHF_SC_R_SHF, shift_amt - 32);
		wrp_immed(nfp_prog, reg_both(dst + 1), 0);
	}

	return 0;
}