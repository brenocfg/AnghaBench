#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union fp_mant128 {int /*<<< orphan*/ * m32; } ;
struct TYPE_2__ {scalar_t__* m32; scalar_t__ m64; } ;
struct fp_ext {int sign; int exp; TYPE_1__ mant; scalar_t__ lowmant; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSR_EXC_DZ ; 
 int /*<<< orphan*/  FPSR_EXC_UNFL ; 
 scalar_t__ IS_INF (struct fp_ext*) ; 
 scalar_t__ IS_ZERO (struct fp_ext*) ; 
 int /*<<< orphan*/  PINSTR ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fp_denormalize (struct fp_ext*,int) ; 
 int /*<<< orphan*/  fp_dividemant (union fp_mant128*,struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_dyadic_check (struct fp_ext*,struct fp_ext*) ; 
 scalar_t__ fp_overnormalize (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_putmant128 (struct fp_ext*,union fp_mant128*,int) ; 
 int /*<<< orphan*/  fp_set_nan (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_ovrflw (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_sr (int /*<<< orphan*/ ) ; 

struct fp_ext *
fp_fdiv(struct fp_ext *dest, struct fp_ext *src)
{
	union fp_mant128 temp;
	int exp;

	dprint(PINSTR, "fdiv\n");

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

	/* shift up the mantissa for denormalized numbers,
	   so that the highest bit is set, this makes lots
	   of things below easier */
	if ((long)dest->mant.m32[0] >= 0)
		exp -= fp_overnormalize(dest);
	if ((long)src->mant.m32[0] >= 0)
		exp -= fp_overnormalize(src);

	/* now, do the 64-bit divide */
	fp_dividemant(&temp, dest, src);

	/* normalize it back to 64 bits and stuff it back into the
	   destination struct */
	if (!temp.m32[0]) {
		exp--;
		fp_putmant128(dest, &temp, 32);
	} else
		fp_putmant128(dest, &temp, 31);

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