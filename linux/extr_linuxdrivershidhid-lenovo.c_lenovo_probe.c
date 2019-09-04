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
struct hid_device_id {int dummy; } ;
struct hid_device {int product; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
#define  USB_DEVICE_ID_LENOVO_CBTKBD 130 
#define  USB_DEVICE_ID_LENOVO_CUSBKBD 129 
#define  USB_DEVICE_ID_LENOVO_TPKBD 128 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 int lenovo_probe_cptkbd (struct hid_device*) ; 
 int lenovo_probe_tpkbd (struct hid_device*) ; 

__attribute__((used)) static int lenovo_probe(struct hid_device *hdev,
		const struct hid_device_id *id)
{
	int ret;

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "hid_parse failed\n");
		goto err;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (ret) {
		hid_err(hdev, "hid_hw_start failed\n");
		goto err;
	}

	switch (hdev->product) {
	case USB_DEVICE_ID_LENOVO_TPKBD:
		ret = lenovo_probe_tpkbd(hdev);
		break;
	case USB_DEVICE_ID_LENOVO_CUSBKBD:
	case USB_DEVICE_ID_LENOVO_CBTKBD:
		ret = lenovo_probe_cptkbd(hdev);
		break;
	default:
		ret = 0;
		break;
	}
	if (ret)
		goto err_hid;

	return 0;
err_hid:
	hid_hw_stop(hdev);
err:
	return ret;
}