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
struct ishtp_cl_driver {int (* reset ) (struct ishtp_cl_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct ishtp_cl_device {TYPE_1__ dev; int /*<<< orphan*/  event_work; int /*<<< orphan*/ * event_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int stub1 (struct ishtp_cl_device*) ; 
 struct ishtp_cl_driver* to_ishtp_cl_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ishtp_cl_device_reset(struct ishtp_cl_device *device)
{
	struct ishtp_cl_driver *driver;
	int ret = 0;

	device->event_cb = NULL;
	cancel_work_sync(&device->event_work);

	driver = to_ishtp_cl_driver(device->dev.driver);
	if (driver && driver->reset)
		ret = driver->reset(device);

	return ret;
}