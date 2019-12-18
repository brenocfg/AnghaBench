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
struct hid_device {int product; } ;

/* Variables and functions */
#define  USB_DEVICE_ID_IBM_SCROLLPOINT_800DPI_OPTICAL 136 
#define  USB_DEVICE_ID_IBM_SCROLLPOINT_800DPI_OPTICAL_PRO 135 
#define  USB_DEVICE_ID_IBM_SCROLLPOINT_III 134 
#define  USB_DEVICE_ID_IBM_SCROLLPOINT_OPTICAL 133 
#define  USB_DEVICE_ID_IBM_SCROLLPOINT_PRO 132 
#define  USB_DEVICE_ID_LENOVO_CBTKBD 131 
#define  USB_DEVICE_ID_LENOVO_CUSBKBD 130 
#define  USB_DEVICE_ID_LENOVO_SCROLLPOINT_OPTICAL 129 
#define  USB_DEVICE_ID_LENOVO_TPKBD 128 
 int lenovo_input_mapping_cptkbd (struct hid_device*,struct hid_input*,struct hid_field*,struct hid_usage*,unsigned long**,int*) ; 
 int lenovo_input_mapping_scrollpoint (struct hid_device*,struct hid_input*,struct hid_field*,struct hid_usage*,unsigned long**,int*) ; 
 int lenovo_input_mapping_tpkbd (struct hid_device*,struct hid_input*,struct hid_field*,struct hid_usage*,unsigned long**,int*) ; 

__attribute__((used)) static int lenovo_input_mapping(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	switch (hdev->product) {
	case USB_DEVICE_ID_LENOVO_TPKBD:
		return lenovo_input_mapping_tpkbd(hdev, hi, field,
							usage, bit, max);
	case USB_DEVICE_ID_LENOVO_CUSBKBD:
	case USB_DEVICE_ID_LENOVO_CBTKBD:
		return lenovo_input_mapping_cptkbd(hdev, hi, field,
							usage, bit, max);
	case USB_DEVICE_ID_IBM_SCROLLPOINT_III:
	case USB_DEVICE_ID_IBM_SCROLLPOINT_PRO:
	case USB_DEVICE_ID_IBM_SCROLLPOINT_OPTICAL:
	case USB_DEVICE_ID_IBM_SCROLLPOINT_800DPI_OPTICAL:
	case USB_DEVICE_ID_IBM_SCROLLPOINT_800DPI_OPTICAL_PRO:
	case USB_DEVICE_ID_LENOVO_SCROLLPOINT_OPTICAL:
		return lenovo_input_mapping_scrollpoint(hdev, hi, field,
							usage, bit, max);
	default:
		return 0;
	}
}