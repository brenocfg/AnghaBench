#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct magicmouse_sc {TYPE_1__* input; } ;
struct hid_usage {int dummy; } ;
struct hid_input {TYPE_1__* input; } ;
struct hid_field {int flags; } ;
struct hid_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ product; } ;
struct TYPE_3__ {TYPE_2__ id; } ;

/* Variables and functions */
 int HID_MAIN_ITEM_RELATIVE ; 
 scalar_t__ USB_DEVICE_ID_APPLE_MAGICTRACKPAD ; 
 scalar_t__ USB_DEVICE_ID_APPLE_MAGICTRACKPAD2 ; 
 struct magicmouse_sc* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int magicmouse_input_mapping(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	struct magicmouse_sc *msc = hid_get_drvdata(hdev);

	if (!msc->input)
		msc->input = hi->input;

	/* Magic Trackpad does not give relative data after switching to MT */
	if ((hi->input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD ||
	     hi->input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) &&
	    field->flags & HID_MAIN_ITEM_RELATIVE)
		return -1;

	return 0;
}