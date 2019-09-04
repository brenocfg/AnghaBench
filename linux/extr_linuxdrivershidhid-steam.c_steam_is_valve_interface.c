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
struct hid_report_enum {int /*<<< orphan*/  report_list; } ;
struct hid_device {struct hid_report_enum* report_enum; } ;

/* Variables and functions */
 size_t HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool steam_is_valve_interface(struct hid_device *hdev)
{
	struct hid_report_enum *rep_enum;

	/*
	 * The wired device creates 3 interfaces:
	 *  0: emulated mouse.
	 *  1: emulated keyboard.
	 *  2: the real game pad.
	 * The wireless device creates 5 interfaces:
	 *  0: emulated keyboard.
	 *  1-4: slots where up to 4 real game pads will be connected to.
	 * We know which one is the real gamepad interface because they are the
	 * only ones with a feature report.
	 */
	rep_enum = &hdev->report_enum[HID_FEATURE_REPORT];
	return !list_empty(&rep_enum->report_list);
}