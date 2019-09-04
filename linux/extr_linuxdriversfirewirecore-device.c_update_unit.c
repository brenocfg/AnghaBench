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
struct fw_unit {int dummy; } ;
struct fw_driver {int /*<<< orphan*/  (* update ) (struct fw_unit*) ;} ;
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 struct fw_unit* fw_unit (struct device*) ; 
 scalar_t__ is_fw_unit (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct fw_unit*) ; 

__attribute__((used)) static int update_unit(struct device *dev, void *data)
{
	struct fw_unit *unit = fw_unit(dev);
	struct fw_driver *driver = (struct fw_driver *)dev->driver;

	if (is_fw_unit(dev) && driver != NULL && driver->update != NULL) {
		device_lock(dev);
		driver->update(unit);
		device_unlock(dev);
	}

	return 0;
}