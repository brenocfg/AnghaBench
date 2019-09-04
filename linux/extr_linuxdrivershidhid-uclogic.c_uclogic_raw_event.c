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
typedef  int u8 ;
struct uclogic_drvdata {scalar_t__ invert_pen_inrange; scalar_t__ has_virtual_pad_interface; } ;
struct hid_report {scalar_t__ type; scalar_t__ id; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HID_INPUT_REPORT ; 
 scalar_t__ UCLOGIC_PEN_REPORT_ID ; 
 struct uclogic_drvdata* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int uclogic_raw_event(struct hid_device *hdev, struct hid_report *report,
			u8 *data, int size)
{
	struct uclogic_drvdata *drvdata = hid_get_drvdata(hdev);

	if ((report->type == HID_INPUT_REPORT) &&
	    (report->id == UCLOGIC_PEN_REPORT_ID) &&
	    (size >= 2)) {
		if (drvdata->has_virtual_pad_interface && (data[1] & 0x20))
			/* Change to virtual frame button report ID */
			data[0] = 0xf7;
		else if (drvdata->invert_pen_inrange)
			/* Invert the in-range bit */
			data[1] ^= 0x40;
	}

	return 0;
}