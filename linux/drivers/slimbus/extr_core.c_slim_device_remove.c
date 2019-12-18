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
struct slim_driver {int /*<<< orphan*/  (* remove ) (struct slim_device*) ;} ;
struct slim_device {int dummy; } ;
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct slim_device*) ; 
 struct slim_device* to_slim_device (struct device*) ; 
 struct slim_driver* to_slim_driver (scalar_t__) ; 

__attribute__((used)) static int slim_device_remove(struct device *dev)
{
	struct slim_device *sbdev = to_slim_device(dev);
	struct slim_driver *sbdrv;

	if (dev->driver) {
		sbdrv = to_slim_driver(dev->driver);
		if (sbdrv->remove)
			sbdrv->remove(sbdev);
	}

	return 0;
}