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
struct udraw {int last_two_finger_x; int last_two_finger_y; int /*<<< orphan*/  accel_input_dev; int /*<<< orphan*/  pen_input_dev; int /*<<< orphan*/  touch_input_dev; int /*<<< orphan*/  joy_input_dev; struct hid_device* hdev; } ;
struct hid_device_id {int dummy; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HID_CONNECT_DRIVER ; 
 int HID_CONNECT_HIDRAW ; 
 struct udraw* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct udraw*) ; 
 scalar_t__ input_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udraw_setup_accel (struct udraw*,struct hid_device*) ; 
 int /*<<< orphan*/  udraw_setup_joypad (struct udraw*,struct hid_device*) ; 
 int /*<<< orphan*/  udraw_setup_pen (struct udraw*,struct hid_device*) ; 
 int /*<<< orphan*/  udraw_setup_touch (struct udraw*,struct hid_device*) ; 

__attribute__((used)) static int udraw_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	struct udraw *udraw;
	int ret;

	udraw = devm_kzalloc(&hdev->dev, sizeof(struct udraw), GFP_KERNEL);
	if (!udraw)
		return -ENOMEM;

	udraw->hdev = hdev;
	udraw->last_two_finger_x = -1;
	udraw->last_two_finger_y = -1;

	hid_set_drvdata(hdev, udraw);

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "parse failed\n");
		return ret;
	}

	if (!udraw_setup_joypad(udraw, hdev) ||
	    !udraw_setup_touch(udraw, hdev) ||
	    !udraw_setup_pen(udraw, hdev) ||
	    !udraw_setup_accel(udraw, hdev)) {
		hid_err(hdev, "could not allocate interfaces\n");
		return -ENOMEM;
	}

	ret = input_register_device(udraw->joy_input_dev) ||
		input_register_device(udraw->touch_input_dev) ||
		input_register_device(udraw->pen_input_dev) ||
		input_register_device(udraw->accel_input_dev);
	if (ret) {
		hid_err(hdev, "failed to register interfaces\n");
		return ret;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW | HID_CONNECT_DRIVER);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		return ret;
	}

	return 0;
}