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
struct slim_driver {int /*<<< orphan*/  id_table; } ;
struct slim_device {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ of_driver_match_device (struct device*,struct device_driver*) ; 
 int /*<<< orphan*/  slim_match (int /*<<< orphan*/ ,struct slim_device*) ; 
 struct slim_device* to_slim_device (struct device*) ; 
 struct slim_driver* to_slim_driver (struct device_driver*) ; 

__attribute__((used)) static int slim_device_match(struct device *dev, struct device_driver *drv)
{
	struct slim_device *sbdev = to_slim_device(dev);
	struct slim_driver *sbdrv = to_slim_driver(drv);

	/* Attempt an OF style match first */
	if (of_driver_match_device(dev, drv))
		return 1;

	return !!slim_match(sbdrv->id_table, sbdev);
}