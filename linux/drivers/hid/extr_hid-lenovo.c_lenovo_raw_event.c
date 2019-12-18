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
struct hid_report {int dummy; } ;
struct hid_device {scalar_t__ product; } ;

/* Variables and functions */
 scalar_t__ USB_DEVICE_ID_LENOVO_CUSBKBD ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lenovo_raw_event(struct hid_device *hdev,
			struct hid_report *report, u8 *data, int size)
{
	/*
	 * Compact USB keyboard's Fn-F12 report holds down many other keys, and
	 * its own key is outside the usage page range. Remove extra
	 * keypresses and remap to inside usage page.
	 */
	if (unlikely(hdev->product == USB_DEVICE_ID_LENOVO_CUSBKBD
			&& size == 3
			&& data[0] == 0x15
			&& data[1] == 0x94
			&& data[2] == 0x01)) {
		data[1] = 0x00;
		data[2] = 0x01;
	}

	return 0;
}