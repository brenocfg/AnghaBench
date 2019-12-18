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
struct intel_th_driver {int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; } ;
struct intel_th_device {scalar_t__ type; int /*<<< orphan*/  name; } ;
struct device_driver {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ INTEL_TH_SWITCH ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_th_device* to_intel_th_device (struct device*) ; 
 struct intel_th_driver* to_intel_th_driver (struct device_driver*) ; 

__attribute__((used)) static int intel_th_match(struct device *dev, struct device_driver *driver)
{
	struct intel_th_driver *thdrv = to_intel_th_driver(driver);
	struct intel_th_device *thdev = to_intel_th_device(dev);

	if (thdev->type == INTEL_TH_SWITCH &&
	    (!thdrv->enable || !thdrv->disable))
		return 0;

	return !strcmp(thdev->name, driver->name);
}