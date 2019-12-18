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
struct hid_usage {scalar_t__ hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;
struct a4tech_sc {int quirks; } ;

/* Variables and functions */
 int A4_2WHEEL_MOUSE_HACK_B8 ; 
 scalar_t__ A4_WHEEL_ORIENTATION ; 
 struct a4tech_sc* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int a4_input_mapping(struct hid_device *hdev, struct hid_input *hi,
			    struct hid_field *field, struct hid_usage *usage,
			    unsigned long **bit, int *max)
{
	struct a4tech_sc *a4 = hid_get_drvdata(hdev);

	if (a4->quirks & A4_2WHEEL_MOUSE_HACK_B8 &&
	    usage->hid == A4_WHEEL_ORIENTATION) {
		/*
		 * We do not want to have this usage mapped to anything as it's
		 * nonstandard and doesn't really behave like an HID report.
		 * It's only selecting the orientation (vertical/horizontal) of
		 * the previous mouse wheel report. The input_events will be
		 * generated once both reports are recorded in a4_event().
		 */
		return -1;
	}

	return 0;

}