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
struct rmi_data {int device_flags; } ;
struct hid_usage {int hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int HID_UP_BUTTON ; 
 int HID_USAGE_PAGE ; 
 int RMI_DEVICE ; 
 int RMI_DEVICE_HAS_PHYS_BUTTONS ; 
 struct rmi_data* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int rmi_input_mapping(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	struct rmi_data *data = hid_get_drvdata(hdev);

	/*
	 * we want to make HID ignore the advertised HID collection
	 * for RMI deivces
	 */
	if (data->device_flags & RMI_DEVICE) {
		if ((data->device_flags & RMI_DEVICE_HAS_PHYS_BUTTONS) &&
		    ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON))
			return 0;

		return -1;
	}

	return 0;
}