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
struct TYPE_2__ {int m64; } ;
struct fp_ext {int sign; TYPE_1__ mant; } ;

/* Variables and functions */
 scalar_t__ IS_INF (struct fp_ext*) ; 
 scalar_t__ IS_ZERO (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_copy_ext (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_dyadic_check (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_fdiv (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_fmul (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_fsub (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_roundint (struct fp_ext*,int) ; 
 int /*<<< orphan*/  fp_set_nan (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_quotient (int) ; 

__attribute__((used)) static struct fp_ext *
modrem_kernel(struct fp_ext *dest, struct fp_ext *src, int mode)
{
	struct fp_ext tmp;

	fp_dyadic_check(dest, src);

	/* Infinities and zeros */
	if (IS_INF(dest) || IS_ZERO(src)) {
		fp_set_nan(dest);
		return dest;
	}
	if (IS_ZERO(dest) || IS_INF(src))
		return dest;

	/* FIXME: there is almost certainly a smarter way to do this */
	fp_copy_ext(&tmp, dest);
	fp_fdiv(&tmp, src);		/* NOTE: src might be modified */
	fp_roundint(&tmp, mode);
	fp_fmul(&tmp, src);
	fp_fsub(dest, &tmp);

	/* set the quotient byte */
	fp_set_quotient((dest->mant.m64 & 0x7f) | (dest->sign << 7));
	return dest;
}