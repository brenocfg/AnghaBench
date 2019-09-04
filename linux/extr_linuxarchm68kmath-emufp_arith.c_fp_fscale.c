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
struct fp_ext {int exp; } ;
struct TYPE_2__ {int rnd; } ;

/* Variables and functions */
 int FPCR_ROUND_RZ ; 
 TYPE_1__* FPDATA ; 
 int /*<<< orphan*/  FPSR_EXC_UNFL ; 
 scalar_t__ IS_INF (struct fp_ext*) ; 
 scalar_t__ IS_ZERO (struct fp_ext*) ; 
 int /*<<< orphan*/  PINSTR ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*) ; 
 int fp_conv_ext2long (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_denormalize (struct fp_ext*,int) ; 
 int /*<<< orphan*/  fp_dyadic_check (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_nan (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_ovrflw (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_sr (int /*<<< orphan*/ ) ; 

struct fp_ext *
fp_fscale(struct fp_ext *dest, struct fp_ext *src)
{
	int scale, oldround;

	dprint(PINSTR, "fscale\n");

	fp_dyadic_check(dest, src);

	/* Infinities */
	if (IS_INF(src)) {
		fp_set_nan(dest);
		return dest;
	}
	if (IS_INF(dest))
		return dest;

	/* zeroes */
	if (IS_ZERO(src) || IS_ZERO(dest))
		return dest;

	/* Source exponent out of range */
	if (src->exp >= 0x400c) {
		fp_set_ovrflw(dest);
		return dest;
	}

	/* src must be rounded with round to zero. */
	oldround = FPDATA->rnd;
	FPDATA->rnd = FPCR_ROUND_RZ;
	scale = fp_conv_ext2long(src);
	FPDATA->rnd = oldround;

	/* new exponent */
	scale += dest->exp;

	if (scale >= 0x7fff) {
		fp_set_ovrflw(dest);
	} else if (scale <= 0) {
		fp_set_sr(FPSR_EXC_UNFL);
		fp_denormalize(dest, -scale);
	} else
		dest->exp = scale;

	return dest;
}