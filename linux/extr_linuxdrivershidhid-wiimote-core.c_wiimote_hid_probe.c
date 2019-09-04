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
struct wiimote_data {int /*<<< orphan*/  accel; int /*<<< orphan*/  ir; TYPE_1__* hdev; } ;
struct hid_device_id {int dummy; } ;
struct hid_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  quirks; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HID_CONNECT_HIDRAW ; 
 int /*<<< orphan*/  HID_QUIRK_NO_INIT_REPORTS ; 
 int /*<<< orphan*/  dev_attr_devtype ; 
 int /*<<< orphan*/  dev_attr_extension ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  hid_hw_close (struct hid_device*) ; 
 int hid_hw_open (struct hid_device*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wiimote_data*) ; 
 int wiidebug_init (struct wiimote_data*) ; 
 struct wiimote_data* wiimote_create (struct hid_device*) ; 
 int /*<<< orphan*/  wiimote_destroy (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_schedule (struct wiimote_data*) ; 

__attribute__((used)) static int wiimote_hid_probe(struct hid_device *hdev,
				const struct hid_device_id *id)
{
	struct wiimote_data *wdata;
	int ret;

	hdev->quirks |= HID_QUIRK_NO_INIT_REPORTS;

	wdata = wiimote_create(hdev);
	if (!wdata) {
		hid_err(hdev, "Can't alloc device\n");
		return -ENOMEM;
	}

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "HID parse failed\n");
		goto err;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	if (ret) {
		hid_err(hdev, "HW start failed\n");
		goto err;
	}

	ret = hid_hw_open(hdev);
	if (ret) {
		hid_err(hdev, "cannot start hardware I/O\n");
		goto err_stop;
	}

	ret = device_create_file(&hdev->dev, &dev_attr_extension);
	if (ret) {
		hid_err(hdev, "cannot create sysfs attribute\n");
		goto err_close;
	}

	ret = device_create_file(&hdev->dev, &dev_attr_devtype);
	if (ret) {
		hid_err(hdev, "cannot create sysfs attribute\n");
		goto err_ext;
	}

	ret = wiidebug_init(wdata);
	if (ret)
		goto err_free;

	hid_info(hdev, "New device registered\n");

	/* schedule device detection */
	wiimote_schedule(wdata);

	return 0;

err_free:
	wiimote_destroy(wdata);
	return ret;

err_ext:
	device_remove_file(&wdata->hdev->dev, &dev_attr_extension);
err_close:
	hid_hw_close(hdev);
err_stop:
	hid_hw_stop(hdev);
err:
	input_free_device(wdata->ir);
	input_free_device(wdata->accel);
	kfree(wdata);
	return ret;
}