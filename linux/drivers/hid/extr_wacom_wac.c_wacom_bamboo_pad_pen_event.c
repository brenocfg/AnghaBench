#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wacom_wac {TYPE_1__* shared; } ;
struct TYPE_2__ {int /*<<< orphan*/  pen; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  WACOM_PKGLEN_PENABLED ; 
 unsigned char WACOM_REPORT_BPAD_PEN ; 
 int /*<<< orphan*/  hid_input_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wacom_bamboo_pad_pen_event(struct wacom_wac *wacom,
		unsigned char *data)
{
	unsigned char prefix;

	/*
	 * We need to reroute the event from the debug interface to the
	 * pen interface.
	 * We need to add the report ID to the actual pen report, so we
	 * temporary overwrite the first byte to prevent having to kzalloc/kfree
	 * and memcpy the report.
	 */
	prefix = data[0];
	data[0] = WACOM_REPORT_BPAD_PEN;

	/*
	 * actually reroute the event.
	 * No need to check if wacom->shared->pen is valid, hid_input_report()
	 * will check for us.
	 */
	hid_input_report(wacom->shared->pen, HID_INPUT_REPORT, data,
			 WACOM_PKGLEN_PENABLED, 1);

	data[0] = prefix;
}