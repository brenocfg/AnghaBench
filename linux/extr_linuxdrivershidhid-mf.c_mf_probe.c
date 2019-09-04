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
struct hid_device_id {int /*<<< orphan*/  driver_data; } ;
struct hid_device {int /*<<< orphan*/  quirks; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HID_CONNECT_DEFAULT ; 
 int HID_CONNECT_FF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 int mf_init (struct hid_device*) ; 

__attribute__((used)) static int mf_probe(struct hid_device *hid, const struct hid_device_id *id)
{
	int error;

	dev_dbg(&hid->dev, "Mayflash HID hardware probe...\n");

	/* Apply quirks as needed */
	hid->quirks |= id->driver_data;

	error = hid_parse(hid);
	if (error) {
		hid_err(hid, "HID parse failed.\n");
		return error;
	}

	error = hid_hw_start(hid, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	if (error) {
		hid_err(hid, "HID hw start failed\n");
		return error;
	}

	error = mf_init(hid);
	if (error) {
		hid_err(hid, "Force feedback init failed.\n");
		hid_hw_stop(hid);
		return error;
	}

	return 0;
}