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
struct hid_usage {int hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;

/* Variables and functions */
#define  HID_GD_RFKILL_BTN 132 
#define  HID_GD_X 131 
#define  HID_GD_Y 130 
#define  HID_UP_DIGITIZER 129 
#define  HID_UP_GENDESK 128 
 int HID_USAGE_PAGE ; 

__attribute__((used)) static int ms_surface_dial_quirk(struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	switch (usage->hid & HID_USAGE_PAGE) {
	case 0xff070000:
		/* fall-through */
	case HID_UP_DIGITIZER:
		/* ignore those axis */
		return -1;
	case HID_UP_GENDESK:
		switch (usage->hid) {
		case HID_GD_X:
			/* fall-through */
		case HID_GD_Y:
			/* fall-through */
		case HID_GD_RFKILL_BTN:
			/* ignore those axis */
			return -1;
		}
	}

	return 0;
}