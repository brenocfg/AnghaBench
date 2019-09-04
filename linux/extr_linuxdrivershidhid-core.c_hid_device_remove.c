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
struct hid_driver {int /*<<< orphan*/  (* remove ) (struct hid_device*) ;} ;
struct hid_device {int io_started; int /*<<< orphan*/  driver_input_lock; struct hid_driver* driver; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_close_report (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  stub1 (struct hid_device*) ; 
 struct hid_device* to_hid_device (struct device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hid_device_remove(struct device *dev)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct hid_driver *hdrv;
	int ret = 0;

	if (down_interruptible(&hdev->driver_input_lock)) {
		ret = -EINTR;
		goto end;
	}
	hdev->io_started = false;

	hdrv = hdev->driver;
	if (hdrv) {
		if (hdrv->remove)
			hdrv->remove(hdev);
		else /* default remove */
			hid_hw_stop(hdev);
		hid_close_report(hdev);
		hdev->driver = NULL;
	}

	if (!hdev->io_started)
		up(&hdev->driver_input_lock);
end:
	return ret;
}