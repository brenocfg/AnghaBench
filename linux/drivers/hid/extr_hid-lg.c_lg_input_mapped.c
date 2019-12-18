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
struct lg_drv_data {int quirks; } ;
struct hid_usage {scalar_t__ type; scalar_t__ code; } ;
struct hid_input {int dummy; } ;
struct hid_field {int flags; int /*<<< orphan*/  application; } ;
struct hid_device {int product; } ;

/* Variables and functions */
 scalar_t__ ABS_RZ ; 
 scalar_t__ ABS_X ; 
 scalar_t__ ABS_Y ; 
 scalar_t__ ABS_Z ; 
 scalar_t__ EV_ABS ; 
 scalar_t__ EV_KEY ; 
 scalar_t__ EV_REL ; 
 int /*<<< orphan*/  HID_GD_MULTIAXIS ; 
 int HID_MAIN_ITEM_RELATIVE ; 
 int LG_BAD_RELATIVE_KEYS ; 
 int LG_DUPLICATE_USAGES ; 
#define  USB_DEVICE_ID_LOGITECH_DFGT_WHEEL 139 
#define  USB_DEVICE_ID_LOGITECH_DFP_WHEEL 138 
#define  USB_DEVICE_ID_LOGITECH_G25_WHEEL 137 
#define  USB_DEVICE_ID_LOGITECH_G27_WHEEL 136 
#define  USB_DEVICE_ID_LOGITECH_G29_WHEEL 135 
#define  USB_DEVICE_ID_LOGITECH_MOMO_WHEEL 134 
#define  USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2 133 
#define  USB_DEVICE_ID_LOGITECH_VIBRATION_WHEEL 132 
#define  USB_DEVICE_ID_LOGITECH_WHEEL 131 
#define  USB_DEVICE_ID_LOGITECH_WII_WHEEL 130 
#define  USB_DEVICE_ID_LOGITECH_WINGMAN_FFG 129 
#define  USB_DEVICE_ID_LOGITECH_WINGMAN_FG 128 
 int /*<<< orphan*/  clear_bit (scalar_t__,unsigned long*) ; 
 struct lg_drv_data* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int lg_input_mapped(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	struct lg_drv_data *drv_data = hid_get_drvdata(hdev);

	if ((drv_data->quirks & LG_BAD_RELATIVE_KEYS) && usage->type == EV_KEY &&
			(field->flags & HID_MAIN_ITEM_RELATIVE))
		field->flags &= ~HID_MAIN_ITEM_RELATIVE;

	if ((drv_data->quirks & LG_DUPLICATE_USAGES) && (usage->type == EV_KEY ||
			 usage->type == EV_REL || usage->type == EV_ABS))
		clear_bit(usage->code, *bit);

	/* Ensure that Logitech wheels are not given a default fuzz/flat value */
	if (usage->type == EV_ABS && (usage->code == ABS_X ||
			usage->code == ABS_Y || usage->code == ABS_Z ||
			usage->code == ABS_RZ)) {
		switch (hdev->product) {
		case USB_DEVICE_ID_LOGITECH_G29_WHEEL:
		case USB_DEVICE_ID_LOGITECH_WINGMAN_FG:
		case USB_DEVICE_ID_LOGITECH_WINGMAN_FFG:
		case USB_DEVICE_ID_LOGITECH_WHEEL:
		case USB_DEVICE_ID_LOGITECH_MOMO_WHEEL:
		case USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
		case USB_DEVICE_ID_LOGITECH_G25_WHEEL:
		case USB_DEVICE_ID_LOGITECH_DFGT_WHEEL:
		case USB_DEVICE_ID_LOGITECH_G27_WHEEL:
		case USB_DEVICE_ID_LOGITECH_WII_WHEEL:
		case USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2:
		case USB_DEVICE_ID_LOGITECH_VIBRATION_WHEEL:
			field->application = HID_GD_MULTIAXIS;
			break;
		default:
			break;
		}
	}

	return 0;
}