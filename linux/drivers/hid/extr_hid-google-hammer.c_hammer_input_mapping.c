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
struct hid_device {scalar_t__ product; } ;

/* Variables and functions */
 scalar_t__ USB_DEVICE_ID_GOOGLE_WHISKERS ; 
 scalar_t__ WHISKERS_KBD_FOLDED ; 

__attribute__((used)) static int hammer_input_mapping(struct hid_device *hdev, struct hid_input *hi,
				struct hid_field *field,
				struct hid_usage *usage,
				unsigned long **bit, int *max)
{
	if (hdev->product == USB_DEVICE_ID_GOOGLE_WHISKERS &&
	    usage->hid == WHISKERS_KBD_FOLDED) {
		/*
		 * We do not want to have this usage mapped as it will get
		 * mixed in with "base attached" signal and delivered over
		 * separate input device for tablet switch mode.
		 */
		return -1;
	}

	return 0;
}