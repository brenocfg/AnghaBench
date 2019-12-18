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
struct input_dev {int dummy; } ;
struct hid_usage {int code; int resolution_multiplier; int wheel_accumulated; } ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EV_REL ; 
 int REL_HWHEEL ; 
 int REL_WHEEL ; 
 int REL_WHEEL_HI_RES ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hidinput_handle_scroll(struct hid_usage *usage,
				   struct input_dev *input,
				   __s32 value)
{
	int code;
	int hi_res, lo_res;

	if (value == 0)
		return;

	if (usage->code == REL_WHEEL_HI_RES)
		code = REL_WHEEL;
	else
		code = REL_HWHEEL;

	/*
	 * Windows reports one wheel click as value 120. Where a high-res
	 * scroll wheel is present, a fraction of 120 is reported instead.
	 * Our REL_WHEEL_HI_RES axis does the same because all HW must
	 * adhere to the 120 expectation.
	 */
	hi_res = value * 120/usage->resolution_multiplier;

	usage->wheel_accumulated += hi_res;
	lo_res = usage->wheel_accumulated/120;
	if (lo_res)
		usage->wheel_accumulated -= lo_res * 120;

	input_event(input, EV_REL, code, lo_res);
	input_event(input, EV_REL, usage->code, hi_res);
}