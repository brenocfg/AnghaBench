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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUL_LAST ; 
 int /*<<< orphan*/  MUL_LAST_2 ; 
 int /*<<< orphan*/  MUL_STEP_1 ; 
 int /*<<< orphan*/  MUL_STEP_2 ; 
 int /*<<< orphan*/  MUL_STEP_3 ; 
 int /*<<< orphan*/  MUL_STEP_4 ; 
 int /*<<< orphan*/  MUL_STEP_NONE ; 
 int /*<<< orphan*/  MUL_TYPE_START ; 
 int /*<<< orphan*/  MUL_TYPE_STEP_32x32 ; 
 int /*<<< orphan*/  emit_mul (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wrp_mul_u32(struct nfp_prog *nfp_prog, swreg dst_hi, swreg dst_lo, swreg lreg,
	    swreg rreg, bool gen_high_half)
{
	emit_mul(nfp_prog, lreg, MUL_TYPE_START, MUL_STEP_NONE, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_32x32, MUL_STEP_1, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_32x32, MUL_STEP_2, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_32x32, MUL_STEP_3, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_32x32, MUL_STEP_4, rreg);
	emit_mul(nfp_prog, dst_lo, MUL_TYPE_STEP_32x32, MUL_LAST, reg_none());
	if (gen_high_half)
		emit_mul(nfp_prog, dst_hi, MUL_TYPE_STEP_32x32, MUL_LAST_2,
			 reg_none());
	else
		wrp_immed(nfp_prog, dst_hi, 0);
}