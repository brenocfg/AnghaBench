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
 struct fixed31_32 dc_fixpt_add (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_from_fraction (int,int) ; 
 struct fixed31_32 dc_fixpt_half ; 
 struct fixed31_32 dc_fixpt_log (int /*<<< orphan*/ ) ; 
 scalar_t__ dc_fixpt_lt (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_mul (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_one ; 
 struct fixed31_32 dc_fixpt_pow (struct fixed31_32,struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_sub (struct fixed31_32,struct fixed31_32) ; 

__attribute__((used)) static void compute_hlg_oetf(struct fixed31_32 in_x, bool is_light0_12, struct fixed31_32 *out_y)
{
	struct fixed31_32 a;
	struct fixed31_32 b;
	struct fixed31_32 c;
	struct fixed31_32 threshold;
	struct fixed31_32 reference_white_level;

	a = dc_fixpt_from_fraction(17883277, 100000000);
	if (is_light0_12) {
		/*light 0-12*/
		b = dc_fixpt_from_fraction(28466892, 100000000);
		c = dc_fixpt_from_fraction(55991073, 100000000);
		threshold = dc_fixpt_one;
		reference_white_level = dc_fixpt_half;
	} else {
		/*light 0-1*/
		b = dc_fixpt_from_fraction(2372241, 100000000);
		c = dc_fixpt_add(dc_fixpt_one, dc_fixpt_from_fraction(429347, 100000000));
		threshold = dc_fixpt_from_fraction(1, 12);
		reference_white_level = dc_fixpt_pow(dc_fixpt_from_fraction(3, 1), dc_fixpt_half);
	}
	if (dc_fixpt_lt(threshold, in_x))
		*out_y = dc_fixpt_add(c, dc_fixpt_mul(a, dc_fixpt_log(dc_fixpt_sub(in_x, b))));
	else
		*out_y = dc_fixpt_mul(dc_fixpt_pow(in_x, dc_fixpt_half), reference_white_level);
}