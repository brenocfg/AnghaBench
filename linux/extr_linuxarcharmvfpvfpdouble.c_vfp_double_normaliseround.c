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
typedef  int u32 ;
struct vfp_double {int exponent; int significand; scalar_t__ sign; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int FPSCR_IXC ; 
 int FPSCR_OFC ; 
 int FPSCR_RMODE_MASK ; 
 int FPSCR_ROUND_NEAREST ; 
 int FPSCR_ROUND_PLUSINF ; 
 int FPSCR_ROUND_TOZERO ; 
 int FPSCR_UFC ; 
 int VFP_DOUBLE_LOW_BITS ; 
 int fls (int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  vfp_double_dump (char*,struct vfp_double*) ; 
 int /*<<< orphan*/  vfp_double_pack (struct vfp_double*) ; 
 int /*<<< orphan*/  vfp_put_double (int /*<<< orphan*/ ,int) ; 
 int vfp_shiftright64jamming (int,int) ; 

u32 vfp_double_normaliseround(int dd, struct vfp_double *vd, u32 fpscr, u32 exceptions, const char *func)
{
	u64 significand, incr;
	int exponent, shift, underflow;
	u32 rmode;

	vfp_double_dump("pack: in", vd);

	/*
	 * Infinities and NaNs are a special case.
	 */
	if (vd->exponent == 2047 && (vd->significand == 0 || exceptions))
		goto pack;

	/*
	 * Special-case zero.
	 */
	if (vd->significand == 0) {
		vd->exponent = 0;
		goto pack;
	}

	exponent = vd->exponent;
	significand = vd->significand;

	shift = 32 - fls(significand >> 32);
	if (shift == 32)
		shift = 64 - fls(significand);
	if (shift) {
		exponent -= shift;
		significand <<= shift;
	}

#ifdef DEBUG
	vd->exponent = exponent;
	vd->significand = significand;
	vfp_double_dump("pack: normalised", vd);
#endif

	/*
	 * Tiny number?
	 */
	underflow = exponent < 0;
	if (underflow) {
		significand = vfp_shiftright64jamming(significand, -exponent);
		exponent = 0;
#ifdef DEBUG
		vd->exponent = exponent;
		vd->significand = significand;
		vfp_double_dump("pack: tiny number", vd);
#endif
		if (!(significand & ((1ULL << (VFP_DOUBLE_LOW_BITS + 1)) - 1)))
			underflow = 0;
	}

	/*
	 * Select rounding increment.
	 */
	incr = 0;
	rmode = fpscr & FPSCR_RMODE_MASK;

	if (rmode == FPSCR_ROUND_NEAREST) {
		incr = 1ULL << VFP_DOUBLE_LOW_BITS;
		if ((significand & (1ULL << (VFP_DOUBLE_LOW_BITS + 1))) == 0)
			incr -= 1;
	} else if (rmode == FPSCR_ROUND_TOZERO) {
		incr = 0;
	} else if ((rmode == FPSCR_ROUND_PLUSINF) ^ (vd->sign != 0))
		incr = (1ULL << (VFP_DOUBLE_LOW_BITS + 1)) - 1;

	pr_debug("VFP: rounding increment = 0x%08llx\n", incr);

	/*
	 * Is our rounding going to overflow?
	 */
	if ((significand + incr) < significand) {
		exponent += 1;
		significand = (significand >> 1) | (significand & 1);
		incr >>= 1;
#ifdef DEBUG
		vd->exponent = exponent;
		vd->significand = significand;
		vfp_double_dump("pack: overflow", vd);
#endif
	}

	/*
	 * If any of the low bits (which will be shifted out of the
	 * number) are non-zero, the result is inexact.
	 */
	if (significand & ((1 << (VFP_DOUBLE_LOW_BITS + 1)) - 1))
		exceptions |= FPSCR_IXC;

	/*
	 * Do our rounding.
	 */
	significand += incr;

	/*
	 * Infinity?
	 */
	if (exponent >= 2046) {
		exceptions |= FPSCR_OFC | FPSCR_IXC;
		if (incr == 0) {
			vd->exponent = 2045;
			vd->significand = 0x7fffffffffffffffULL;
		} else {
			vd->exponent = 2047;		/* infinity */
			vd->significand = 0;
		}
	} else {
		if (significand >> (VFP_DOUBLE_LOW_BITS + 1) == 0)
			exponent = 0;
		if (exponent || significand > 0x8000000000000000ULL)
			underflow = 0;
		if (underflow)
			exceptions |= FPSCR_UFC;
		vd->exponent = exponent;
		vd->significand = significand >> 1;
	}

 pack:
	vfp_double_dump("pack: final", vd);
	{
		s64 d = vfp_double_pack(vd);
		pr_debug("VFP: %s: d(d%d)=%016llx exceptions=%08x\n", func,
			 dd, d, exceptions);
		vfp_put_double(d, dd);
	}
	return exceptions;
}