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
typedef  int u8 ;
struct lg_drv_data {struct lg4ff_device_entry* device_props; } ;
struct TYPE_2__ {int product_id; scalar_t__ combine; } ;
struct lg4ff_device_entry {TYPE_1__ wdata; } ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
#define  USB_DEVICE_ID_LOGITECH_DFGT_WHEEL 137 
#define  USB_DEVICE_ID_LOGITECH_DFP_WHEEL 136 
#define  USB_DEVICE_ID_LOGITECH_G25_WHEEL 135 
#define  USB_DEVICE_ID_LOGITECH_G27_WHEEL 134 
#define  USB_DEVICE_ID_LOGITECH_G29_WHEEL 133 
#define  USB_DEVICE_ID_LOGITECH_MOMO_WHEEL 132 
#define  USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2 131 
#define  USB_DEVICE_ID_LOGITECH_WHEEL 130 
#define  USB_DEVICE_ID_LOGITECH_WII_WHEEL 129 
#define  USB_DEVICE_ID_LOGITECH_WINGMAN_FFG 128 

int lg4ff_raw_event(struct hid_device *hdev, struct hid_report *report,
		u8 *rd, int size, struct lg_drv_data *drv_data)
{
	int offset;
	struct lg4ff_device_entry *entry = drv_data->device_props;

	if (!entry)
		return 0;

	/* adjust HID report present combined pedals data */
	if (entry->wdata.combine) {
		switch (entry->wdata.product_id) {
		case USB_DEVICE_ID_LOGITECH_WHEEL:
			rd[5] = rd[3];
			rd[6] = 0x7F;
			return 1;
		case USB_DEVICE_ID_LOGITECH_WINGMAN_FFG:
		case USB_DEVICE_ID_LOGITECH_MOMO_WHEEL:
		case USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2:
			rd[4] = rd[3];
			rd[5] = 0x7F;
			return 1;
		case USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
			rd[5] = rd[4];
			rd[6] = 0x7F;
			return 1;
		case USB_DEVICE_ID_LOGITECH_G25_WHEEL:
		case USB_DEVICE_ID_LOGITECH_G27_WHEEL:
			offset = 5;
			break;
		case USB_DEVICE_ID_LOGITECH_DFGT_WHEEL:
		case USB_DEVICE_ID_LOGITECH_G29_WHEEL:
			offset = 6;
			break;
		case USB_DEVICE_ID_LOGITECH_WII_WHEEL:
			offset = 3;
			break;
		default:
			return 0;
		}

		/* Compute a combined axis when wheel does not supply it */
		rd[offset] = (0xFF + rd[offset] - rd[offset+1]) >> 1;
		rd[offset+1] = 0x7F;
		return 1;
	}

	return 0;
}