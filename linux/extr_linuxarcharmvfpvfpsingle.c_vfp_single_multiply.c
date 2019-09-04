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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vfp_single {int exponent; int sign; int significand; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSCR_IOC ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int vfp_hi64to32jamming (int) ; 
 int /*<<< orphan*/  vfp_propagate_nan (struct vfp_single*,struct vfp_single*,struct vfp_single*,int /*<<< orphan*/ ) ; 
 struct vfp_single vfp_single_default_qnan ; 
 int /*<<< orphan*/  vfp_single_dump (char*,struct vfp_single*) ; 

__attribute__((used)) static u32
vfp_single_multiply(struct vfp_single *vsd, struct vfp_single *vsn, struct vfp_single *vsm, u32 fpscr)
{
	vfp_single_dump("VSN", vsn);
	vfp_single_dump("VSM", vsm);

	/*
	 * Ensure that 'n' is the largest magnitude number.  Note that
	 * if 'n' and 'm' have equal exponents, we do not swap them.
	 * This ensures that NaN propagation works correctly.
	 */
	if (vsn->exponent < vsm->exponent) {
		struct vfp_single *t = vsn;
		vsn = vsm;
		vsm = t;
		pr_debug("VFP: swapping M <-> N\n");
	}

	vsd->sign = vsn->sign ^ vsm->sign;

	/*
	 * If 'n' is an infinity or NaN, handle it.  'm' may be anything.
	 */
	if (vsn->exponent == 255) {
		if (vsn->significand || (vsm->exponent == 255 && vsm->significand))
			return vfp_propagate_nan(vsd, vsn, vsm, fpscr);
		if ((vsm->exponent | vsm->significand) == 0) {
			*vsd = vfp_single_default_qnan;
			return FPSCR_IOC;
		}
		vsd->exponent = vsn->exponent;
		vsd->significand = 0;
		return 0;
	}

	/*
	 * If 'm' is zero, the result is always zero.  In this case,
	 * 'n' may be zero or a number, but it doesn't matter which.
	 */
	if ((vsm->exponent | vsm->significand) == 0) {
		vsd->exponent = 0;
		vsd->significand = 0;
		return 0;
	}

	/*
	 * We add 2 to the destination exponent for the same reason as
	 * the addition case - though this time we have +1 from each
	 * input operand.
	 */
	vsd->exponent = vsn->exponent + vsm->exponent - 127 + 2;
	vsd->significand = vfp_hi64to32jamming((u64)vsn->significand * vsm->significand);

	vfp_single_dump("VSD", vsd);
	return 0;
}