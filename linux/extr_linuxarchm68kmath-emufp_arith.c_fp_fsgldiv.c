#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* m32; scalar_t__ m64; } ;
struct fp_ext {int sign; int exp; TYPE_1__ mant; scalar_t__ lowmant; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSR_EXC_DZ ; 
 int /*<<< orphan*/  FPSR_EXC_UNFL ; 
 scalar_t__ IS_INF (struct fp_ext*) ; 
 scalar_t__ IS_ZERO (struct fp_ext*) ; 
 int /*<<< orphan*/  PINSTR ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fp_denormalize (struct fp_ext*,int) ; 
 int /*<<< orphan*/  fp_div64 (unsigned long,unsigned long,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fp_dyadic_check (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_nan (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_ovrflw (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_sr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_sub64 (TYPE_1__,TYPE_1__) ; 

struct fp_ext *
fp_fsgldiv(struct fp_ext *dest, struct fp_ext *src)
{
	int exp;
	unsigned long quot, rem;

	dprint(PINSTR, "fsgldiv\n");

	fp_dyadic_check(dest, src);

	/* calculate the correct sign now, as it's necessary for infinities */
	dest->sign = src->sign ^ dest->sign;

	/* Handle infinities */
	if (IS_INF(dest)) {
		/* infinity / infinity = NaN (quiet, as always) */
		if (IS_INF(src))
			fp_set_nan(dest);
		/* infinity / anything else = infinity (with approprate sign) */
		return dest;
	}
	if (IS_INF(src)) {
		/* anything / infinity = zero (with appropriate sign) */
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->lowmant = 0;

		return dest;
	}

	/* zeroes */
	if (IS_ZERO(dest)) {
		/* zero / zero = NaN */
		if (IS_ZERO(src))
			fp_set_nan(dest);
		/* zero / anything else = zero */
		return dest;
	}
	if (IS_ZERO(src)) {
		/* anything / zero = infinity (with appropriate sign) */
		fp_set_sr(FPSR_EXC_DZ);
		dest->exp = 0x7fff;
		dest->mant.m64 = 0;

		return dest;
	}

	exp = dest->exp - src->exp + 0x3fff;

	dest->mant.m32[0] &= 0xffffff00;
	src->mant.m32[0] &= 0xffffff00;

	/* do the 32-bit divide */
	if (dest->mant.m32[0] >= src->mant.m32[0]) {
		fp_sub64(dest->mant, src->mant);
		fp_div64(quot, rem, dest->mant.m32[0], 0, src->mant.m32[0]);
		dest->mant.m32[0] = 0x80000000 | (quot >> 1);
		dest->mant.m32[1] = (quot & 1) | rem;	/* only for rounding */
	} else {
		fp_div64(quot, rem, dest->mant.m32[0], 0, src->mant.m32[0]);
		dest->mant.m32[0] = quot;
		dest->mant.m32[1] = rem;		/* only for rounding */
		exp--;
	}

	if (exp >= 0x7fff) {
		fp_set_ovrflw(dest);
		return dest;
	}
	dest->exp = exp;
	if (exp < 0) {
		fp_set_sr(FPSR_EXC_UNFL);
		fp_denormalize(dest, -exp);
	}

	return dest;
}