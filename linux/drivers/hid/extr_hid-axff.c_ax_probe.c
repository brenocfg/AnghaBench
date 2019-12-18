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
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HID_CONNECT_DEFAULT ; 
 int HID_CONNECT_FF ; 
 int axff_init (struct hid_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_open (struct hid_device*) ; 
 int hid_hw_start (struct hid_device*,int) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,int) ; 

__attribute__((used)) static int ax_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int error;

	dev_dbg(&hdev->dev, "ACRUX HID hardware probe...\n");

	error = hid_parse(hdev);
	if (error) {
		hid_err(hdev, "parse failed\n");
		return error;
	}

	error = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	if (error) {
		hid_err(hdev, "hw start failed\n");
		return error;
	}

	error = axff_init(hdev);
	if (error) {
		/*
		 * Do not fail device initialization completely as device
		 * may still be partially operable, just warn.
		 */
		hid_warn(hdev,
			 "Failed to enable force feedback support, error: %d\n",
			 error);
	}

	/*
	 * We need to start polling device right away, otherwise
	 * it will go into a coma.
	 */
	error = hid_hw_open(hdev);
	if (error) {
		dev_err(&hdev->dev, "hw open failed\n");
		hid_hw_stop(hdev);
		return error;
	}

	return 0;
}