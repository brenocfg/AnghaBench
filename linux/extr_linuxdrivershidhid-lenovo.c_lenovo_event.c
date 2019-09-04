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
struct hid_field {int dummy; } ;
struct hid_device {int product; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
#define  USB_DEVICE_ID_LENOVO_CBTKBD 129 
#define  USB_DEVICE_ID_LENOVO_CUSBKBD 128 
 int lenovo_event_cptkbd (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lenovo_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	switch (hdev->product) {
	case USB_DEVICE_ID_LENOVO_CUSBKBD:
	case USB_DEVICE_ID_LENOVO_CBTKBD:
		return lenovo_event_cptkbd(hdev, field, usage, value);
	default:
		return 0;
	}
}