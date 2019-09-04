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
struct hid_device {scalar_t__ product; } ;
typedef  int __u8 ;

/* Variables and functions */
 scalar_t__ USB_DEVICE_ID_TEXAS_INSTRUMENTS_LENOVO_YOGA ; 

__attribute__((used)) static __u8 *sensor_hub_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	/*
	 * Checks if the report descriptor of Thinkpad Helix 2 has a logical
	 * minimum for magnetic flux axis greater than the maximum.
	 */
	if (hdev->product == USB_DEVICE_ID_TEXAS_INSTRUMENTS_LENOVO_YOGA &&
		*rsize == 2558 && rdesc[913] == 0x17 && rdesc[914] == 0x40 &&
		rdesc[915] == 0x81 && rdesc[916] == 0x08 &&
		rdesc[917] == 0x00 && rdesc[918] == 0x27 &&
		rdesc[921] == 0x07 && rdesc[922] == 0x00) {
		/* Sets negative logical minimum for mag x, y and z */
		rdesc[914] = rdesc[935] = rdesc[956] = 0xc0;
		rdesc[915] = rdesc[936] = rdesc[957] = 0x7e;
		rdesc[916] = rdesc[937] = rdesc[958] = 0xf7;
		rdesc[917] = rdesc[938] = rdesc[959] = 0xff;
	}

	return rdesc;
}