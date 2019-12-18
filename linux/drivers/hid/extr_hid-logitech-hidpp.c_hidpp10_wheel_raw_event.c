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
typedef  scalar_t__ u8 ;
struct hidpp_device {int /*<<< orphan*/  input; } ;
typedef  int s8 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HIDPP_SUB_ID_ROLLER ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_HWHEEL_HI_RES ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_WHEEL_HI_RES ; 
 scalar_t__ REPORT_ID_HIDPP_SHORT ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidpp10_wheel_raw_event(struct hidpp_device *hidpp,
				   u8 *data, int size)
{
	s8 value, hvalue;

	if (!hidpp->input)
		return -EINVAL;

	if (size < 7)
		return 0;

	if (data[0] != REPORT_ID_HIDPP_SHORT || data[2] != HIDPP_SUB_ID_ROLLER)
		return 0;

	value = data[3];
	hvalue = data[4];

	input_report_rel(hidpp->input, REL_WHEEL, value);
	input_report_rel(hidpp->input, REL_WHEEL_HI_RES, value * 120);
	input_report_rel(hidpp->input, REL_HWHEEL, hvalue);
	input_report_rel(hidpp->input, REL_HWHEEL_HI_RES, hvalue * 120);
	input_sync(hidpp->input);

	return 1;
}