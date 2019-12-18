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
struct hid_input {TYPE_1__* input; } ;
struct hid_device {int product; } ;
struct TYPE_2__ {int /*<<< orphan*/  propbit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
 int /*<<< orphan*/  INPUT_PROP_POINTING_STICK ; 
#define  USB_DEVICE_ID_LENOVO_CBTKBD 130 
#define  USB_DEVICE_ID_LENOVO_CUSBKBD 129 
#define  USB_DEVICE_ID_LENOVO_TPKBD 128 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lenovo_input_configured(struct hid_device *hdev,
		struct hid_input *hi)
{
	switch (hdev->product) {
		case USB_DEVICE_ID_LENOVO_TPKBD:
		case USB_DEVICE_ID_LENOVO_CUSBKBD:
		case USB_DEVICE_ID_LENOVO_CBTKBD:
			if (test_bit(EV_REL, hi->input->evbit)) {
				/* set only for trackpoint device */
				__set_bit(INPUT_PROP_POINTER, hi->input->propbit);
				__set_bit(INPUT_PROP_POINTING_STICK,
						hi->input->propbit);
			}
			break;
	}

	return 0;
}