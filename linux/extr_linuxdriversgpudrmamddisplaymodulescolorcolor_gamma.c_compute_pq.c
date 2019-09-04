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
struct fixed31_32 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_fixpt_add (struct fixed31_32 const,int /*<<< orphan*/ ) ; 
 struct fixed31_32 dc_fixpt_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fixed31_32 dc_fixpt_from_fraction (int,int) ; 
 scalar_t__ dc_fixpt_lt (struct fixed31_32,struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_mul (struct fixed31_32 const,struct fixed31_32) ; 
 struct fixed31_32 const dc_fixpt_one ; 
 struct fixed31_32 dc_fixpt_pow (struct fixed31_32,struct fixed31_32 const) ; 
 struct fixed31_32 dc_fixpt_zero ; 

__attribute__((used)) static void compute_pq(struct fixed31_32 in_x, struct fixed31_32 *out_y)
{
	/* consts for PQ gamma formula. */
	const struct fixed31_32 m1 =
		dc_fixpt_from_fraction(159301758, 1000000000);
	const struct fixed31_32 m2 =
		dc_fixpt_from_fraction(7884375, 100000);
	const struct fixed31_32 c1 =
		dc_fixpt_from_fraction(8359375, 10000000);
	const struct fixed31_32 c2 =
		dc_fixpt_from_fraction(188515625, 10000000);
	const struct fixed31_32 c3 =
		dc_fixpt_from_fraction(186875, 10000);

	struct fixed31_32 l_pow_m1;
	struct fixed31_32 base;

	if (dc_fixpt_lt(in_x, dc_fixpt_zero))
		in_x = dc_fixpt_zero;

	l_pow_m1 = dc_fixpt_pow(in_x, m1);
	base = dc_fixpt_div(
			dc_fixpt_add(c1,
					(dc_fixpt_mul(c2, l_pow_m1))),
			dc_fixpt_add(dc_fixpt_one,
					(dc_fixpt_mul(c3, l_pow_m1))));
	*out_y = dc_fixpt_pow(base, m2);
}