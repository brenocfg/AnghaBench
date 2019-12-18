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
struct visor_driver {int (* pause ) (struct visor_device*,int /*<<< orphan*/ ) ;int (* resume ) (struct visor_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct visor_device {int pausing; int resuming; TYPE_1__ device; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  pause_state_change_complete ; 
 int /*<<< orphan*/  publish_vbus_dev_info (struct visor_device*) ; 
 int /*<<< orphan*/  resume_state_change_complete ; 
 int stub1 (struct visor_device*,int /*<<< orphan*/ ) ; 
 int stub2 (struct visor_device*,int /*<<< orphan*/ ) ; 
 struct visor_driver* to_visor_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int visorchipset_initiate_device_pause_resume(struct visor_device *dev,
						     bool is_pause)
{
	int err;
	struct visor_driver *drv;

	/* If no driver associated with the device nothing to pause/resume */
	if (!dev->device.driver)
		return 0;
	if (dev->pausing || dev->resuming)
		return -EBUSY;

	drv = to_visor_driver(dev->device.driver);
	if (is_pause) {
		dev->pausing = true;
		err = drv->pause(dev, pause_state_change_complete);
	} else {
		/*
		 * The vbus_dev_info structure in the channel was been cleared,
		 * make sure it is valid.
		 */
		publish_vbus_dev_info(dev);
		dev->resuming = true;
		err = drv->resume(dev, resume_state_change_complete);
	}
	return err;
}