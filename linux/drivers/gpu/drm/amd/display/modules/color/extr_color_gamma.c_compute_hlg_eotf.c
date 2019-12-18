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
typedef  int uint32_t ;
struct fixed31_32 {int dummy; } ;

/* Variables and functions */
 struct fixed31_32 dc_fixpt_add (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_div (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_div_int (struct fixed31_32,int) ; 
 struct fixed31_32 dc_fixpt_exp (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_from_fraction (int,int) ; 
 scalar_t__ dc_fixpt_lt (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_mul (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_sub (struct fixed31_32,struct fixed31_32) ; 

__attribute__((used)) static void compute_hlg_eotf(struct fixed31_32 in_x,
		struct fixed31_32 *out_y,
		uint32_t sdr_white_level, uint32_t max_luminance_nits)
{
	struct fixed31_32 a;
	struct fixed31_32 b;
	struct fixed31_32 c;
	struct fixed31_32 threshold;
	struct fixed31_32 x;

	struct fixed31_32 scaling_factor =
			dc_fixpt_from_fraction(max_luminance_nits, sdr_white_level);
	a = dc_fixpt_from_fraction(17883277, 100000000);
	b = dc_fixpt_from_fraction(28466892, 100000000);
	c = dc_fixpt_from_fraction(55991073, 100000000);
	threshold = dc_fixpt_from_fraction(1, 2);

	if (dc_fixpt_lt(in_x, threshold)) {
		x = dc_fixpt_mul(in_x, in_x);
		x = dc_fixpt_div_int(x, 3);
	} else {
		x = dc_fixpt_sub(in_x, c);
		x = dc_fixpt_div(x, a);
		x = dc_fixpt_exp(x);
		x = dc_fixpt_add(x, b);
		x = dc_fixpt_div_int(x, 12);
	}
	*out_y = dc_fixpt_mul(x, scaling_factor);

}