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
 struct fixed31_32 dc_fixpt_div (struct fixed31_32,struct fixed31_32) ; 
 scalar_t__ dc_fixpt_le (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_mul (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_neg (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_one ; 
 struct fixed31_32 dc_fixpt_pow (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_sub (struct fixed31_32,struct fixed31_32) ; 

__attribute__((used)) static struct fixed31_32 translate_to_linear_space(
	struct fixed31_32 arg,
	struct fixed31_32 a0,
	struct fixed31_32 a1,
	struct fixed31_32 a2,
	struct fixed31_32 a3,
	struct fixed31_32 gamma)
{
	struct fixed31_32 linear;

	a0 = dc_fixpt_mul(a0, a1);
	if (dc_fixpt_le(arg, dc_fixpt_neg(a0)))

		linear = dc_fixpt_neg(
				 dc_fixpt_pow(
				 dc_fixpt_div(
				 dc_fixpt_sub(a2, arg),
				 dc_fixpt_add(
				 dc_fixpt_one, a3)), gamma));

	else if (dc_fixpt_le(dc_fixpt_neg(a0), arg) &&
			 dc_fixpt_le(arg, a0))
		linear = dc_fixpt_div(arg, a1);
	else
		linear =  dc_fixpt_pow(
					dc_fixpt_div(
					dc_fixpt_add(a2, arg),
					dc_fixpt_add(
					dc_fixpt_one, a3)), gamma);

	return linear;
}