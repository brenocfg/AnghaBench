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
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 struct fixed31_32 dc_fixpt_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_div_int (int /*<<< orphan*/ ,unsigned int) ; 
 struct fixed31_32 dc_fixpt_from_fraction (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dc_fixpt_lt (struct fixed31_32,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_mul (struct fixed31_32,struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_one ; 

__attribute__((used)) static struct fixed31_32 fixed31_32_exp_from_taylor_series(struct fixed31_32 arg)
{
	unsigned int n = 9;

	struct fixed31_32 res = dc_fixpt_from_fraction(
		n + 2,
		n + 1);
	/* TODO find correct res */

	ASSERT(dc_fixpt_lt(arg, dc_fixpt_one));

	do
		res = dc_fixpt_add(
			dc_fixpt_one,
			dc_fixpt_div_int(
				dc_fixpt_mul(
					arg,
					res),
				n));
	while (--n != 1);

	return dc_fixpt_add(
		dc_fixpt_one,
		dc_fixpt_mul(
			arg,
			res));
}