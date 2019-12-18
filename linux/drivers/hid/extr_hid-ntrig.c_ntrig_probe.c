#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ntrig_data {int reading_mt; int sensor_logical_width; int sensor_logical_height; int sensor_physical_width; int sensor_physical_height; int /*<<< orphan*/  deactivate_slack; void* act_state; void* activate_slack; scalar_t__ min_height; scalar_t__ min_width; } ;
struct hid_report {int dummy; } ;
struct hid_device_id {scalar_t__ driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct hid_device {int quirks; TYPE_2__ dev; TYPE_1__* report_enum; } ;
struct TYPE_3__ {struct hid_report** report_id_hash; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HID_CONNECT_DEFAULT ; 
 int HID_CONNECT_FF ; 
 size_t HID_FEATURE_REPORT ; 
 int HID_QUIRK_MULTI_INPUT ; 
 int HID_QUIRK_NO_INIT_REPORTS ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 void* activate_slack ; 
 int /*<<< orphan*/  deactivate_slack ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,struct hid_report*,int /*<<< orphan*/ ) ; 
 int hid_hw_start (struct hid_device*,int) ; 
 int /*<<< orphan*/  hid_hw_wait (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct ntrig_data*) ; 
 int /*<<< orphan*/  kfree (struct ntrig_data*) ; 
 struct ntrig_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntrig_attribute_group ; 
 int ntrig_get_mode (struct hid_device*) ; 
 int /*<<< orphan*/  ntrig_report_version (struct hid_device*) ; 
 int /*<<< orphan*/  ntrig_set_mode (struct hid_device*,int) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ntrig_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;
	struct ntrig_data *nd;
	struct hid_report *report;

	if (id->driver_data)
		hdev->quirks |= HID_QUIRK_MULTI_INPUT
				| HID_QUIRK_NO_INIT_REPORTS;

	nd = kmalloc(sizeof(struct ntrig_data), GFP_KERNEL);
	if (!nd) {
		hid_err(hdev, "cannot allocate N-Trig data\n");
		return -ENOMEM;
	}

	nd->reading_mt = false;
	nd->min_width = 0;
	nd->min_height = 0;
	nd->activate_slack = activate_slack;
	nd->act_state = activate_slack;
	nd->deactivate_slack = -deactivate_slack;
	nd->sensor_logical_width = 1;
	nd->sensor_logical_height = 1;
	nd->sensor_physical_width = 1;
	nd->sensor_physical_height = 1;

	hid_set_drvdata(hdev, nd);

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "parse failed\n");
		goto err_free;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		goto err_free;
	}

	/* This is needed for devices with more recent firmware versions */
	report = hdev->report_enum[HID_FEATURE_REPORT].report_id_hash[0x0a];
	if (report) {
		/* Let the device settle to ensure the wakeup message gets
		 * through */
		hid_hw_wait(hdev);
		hid_hw_request(hdev, report, HID_REQ_GET_REPORT);

		/*
		 * Sanity check: if the current mode is invalid reset it to
		 * something reasonable.
		 */
		if (ntrig_get_mode(hdev) >= 4)
			ntrig_set_mode(hdev, 3);
	}

	ntrig_report_version(hdev);

	ret = sysfs_create_group(&hdev->dev.kobj,
			&ntrig_attribute_group);
	if (ret)
		hid_err(hdev, "cannot create sysfs group\n");

	return 0;
err_free:
	kfree(nd);
	return ret;
}