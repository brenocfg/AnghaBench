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
struct ishtp_cl_driver {int (* remove ) (struct ishtp_cl_device*) ;} ;
struct ishtp_cl_device {int /*<<< orphan*/  event_work; int /*<<< orphan*/ * event_cb; } ;
struct device {int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int stub1 (struct ishtp_cl_device*) ; 
 struct ishtp_cl_device* to_ishtp_cl_device (struct device*) ; 
 struct ishtp_cl_driver* to_ishtp_cl_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ishtp_cl_device_remove(struct device *dev)
{
	struct ishtp_cl_device *device = to_ishtp_cl_device(dev);
	struct ishtp_cl_driver *driver;

	if (!device || !dev->driver)
		return 0;

	if (device->event_cb) {
		device->event_cb = NULL;
		cancel_work_sync(&device->event_work);
	}

	driver = to_ishtp_cl_driver(dev->driver);
	if (!driver->remove) {
		dev->driver = NULL;

		return 0;
	}

	return driver->remove(device);
}