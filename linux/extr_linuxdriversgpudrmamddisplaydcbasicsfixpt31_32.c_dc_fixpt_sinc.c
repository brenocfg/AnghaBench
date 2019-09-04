#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fixed31_32 {scalar_t__ value; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_fixpt_abs (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_div (int /*<<< orphan*/ ,struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_div_int (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dc_fixpt_le (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_mul (struct fixed31_32,struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_mul_int (TYPE_1__,int) ; 
 struct fixed31_32 dc_fixpt_one ; 
 struct fixed31_32 dc_fixpt_sqr (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_sub (struct fixed31_32,int /*<<< orphan*/ ) ; 
 TYPE_1__ dc_fixpt_two_pi ; 
 scalar_t__ div64_s64 (scalar_t__,int /*<<< orphan*/ ) ; 

struct fixed31_32 dc_fixpt_sinc(struct fixed31_32 arg)
{
	struct fixed31_32 square;

	struct fixed31_32 res = dc_fixpt_one;

	int n = 27;

	struct fixed31_32 arg_norm = arg;

	if (dc_fixpt_le(
		dc_fixpt_two_pi,
		dc_fixpt_abs(arg))) {
		arg_norm = dc_fixpt_sub(
			arg_norm,
			dc_fixpt_mul_int(
				dc_fixpt_two_pi,
				(int)div64_s64(
					arg_norm.value,
					dc_fixpt_two_pi.value)));
	}

	square = dc_fixpt_sqr(arg_norm);

	do {
		res = dc_fixpt_sub(
			dc_fixpt_one,
			dc_fixpt_div_int(
				dc_fixpt_mul(
					square,
					res),
				n * (n - 1)));

		n -= 2;
	} while (n > 2);

	if (arg.value != arg_norm.value)
		res = dc_fixpt_div(
			dc_fixpt_mul(res, arg_norm),
			arg);

	return res;
}