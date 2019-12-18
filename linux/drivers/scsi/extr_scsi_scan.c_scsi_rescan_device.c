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
struct scsi_driver {int /*<<< orphan*/  (* rescan ) (struct device*) ;} ;
struct scsi_device {TYPE_1__* handler; } ;
struct device {TYPE_2__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rescan ) (struct scsi_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_attach_vpd (struct scsi_device*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_device*) ; 
 int /*<<< orphan*/  stub2 (struct device*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 
 struct scsi_driver* to_scsi_driver (TYPE_2__*) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

void scsi_rescan_device(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);

	device_lock(dev);

	scsi_attach_vpd(sdev);

	if (sdev->handler && sdev->handler->rescan)
		sdev->handler->rescan(sdev);

	if (dev->driver && try_module_get(dev->driver->owner)) {
		struct scsi_driver *drv = to_scsi_driver(dev->driver);

		if (drv->rescan)
			drv->rescan(dev);
		module_put(dev->driver->owner);
	}
	device_unlock(dev);
}