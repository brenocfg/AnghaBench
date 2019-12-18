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
struct hid_usage {int dummy; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {scalar_t__ product; } ;

/* Variables and functions */
 scalar_t__ USB_DEVICE_ID_SAMSUNG_WIRELESS_KBD_MOUSE ; 
 int samsung_kbd_mouse_input_mapping (struct hid_device*,struct hid_input*,struct hid_field*,struct hid_usage*,unsigned long**,int*) ; 

__attribute__((used)) static int samsung_input_mapping(struct hid_device *hdev, struct hid_input *hi,
	struct hid_field *field, struct hid_usage *usage,
	unsigned long **bit, int *max)
{
	int ret = 0;

	if (USB_DEVICE_ID_SAMSUNG_WIRELESS_KBD_MOUSE == hdev->product)
		ret = samsung_kbd_mouse_input_mapping(hdev,
			hi, field, usage, bit, max);

	return ret;
}