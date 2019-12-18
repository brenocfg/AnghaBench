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
struct hid_device_id {int driver_data; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;
struct elan_drvdata {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int ELAN_HAS_LED ; 
 int ENAVAIL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 struct elan_drvdata* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int elan_init_mute_led (struct hid_device*) ; 
 int elan_start_multitouch (struct hid_device*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct elan_drvdata*) ; 
 scalar_t__ is_not_elan_touchpad (struct hid_device*) ; 

__attribute__((used)) static int elan_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;
	struct elan_drvdata *drvdata;

	drvdata = devm_kzalloc(&hdev->dev, sizeof(*drvdata), GFP_KERNEL);

	if (!drvdata)
		return -ENOMEM;

	hid_set_drvdata(hdev, drvdata);

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "Hid Parse failed\n");
		return ret;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (ret) {
		hid_err(hdev, "Hid hw start failed\n");
		return ret;
	}

	if (is_not_elan_touchpad(hdev))
		return 0;

	if (!drvdata->input) {
		hid_err(hdev, "Input device is not registered\n");
		ret = -ENAVAIL;
		goto err;
	}

	ret = elan_start_multitouch(hdev);
	if (ret)
		goto err;

	if (id->driver_data & ELAN_HAS_LED) {
		ret = elan_init_mute_led(hdev);
		if (ret)
			goto err;
	}

	return 0;
err:
	hid_hw_stop(hdev);
	return ret;
}