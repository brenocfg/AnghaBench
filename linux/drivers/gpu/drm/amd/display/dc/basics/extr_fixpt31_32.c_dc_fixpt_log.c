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
struct fixed31_32 {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned long long abs_i64 (scalar_t__) ; 
 struct fixed31_32 dc_fixpt_add (struct fixed31_32,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_div (struct fixed31_32,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_exp (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_neg (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_one ; 
 struct fixed31_32 dc_fixpt_sub (struct fixed31_32,struct fixed31_32) ; 

struct fixed31_32 dc_fixpt_log(struct fixed31_32 arg)
{
	struct fixed31_32 res = dc_fixpt_neg(dc_fixpt_one);
	/* TODO improve 1st estimation */

	struct fixed31_32 error;

	ASSERT(arg.value > 0);
	/* TODO if arg is negative, return NaN */
	/* TODO if arg is zero, return -INF */

	do {
		struct fixed31_32 res1 = dc_fixpt_add(
			dc_fixpt_sub(
				res,
				dc_fixpt_one),
			dc_fixpt_div(
				arg,
				dc_fixpt_exp(res)));

		error = dc_fixpt_sub(
			res,
			res1);

		res = res1;
		/* TODO determine max_allowed_error based on quality of exp() */
	} while (abs_i64(error.value) > 100ULL);

	return res;
}