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
struct visor_driver {TYPE_1__* channel_types; } ;
struct device_driver {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {struct device_driver* driver; struct bus_type* bus; } ;
struct bus_type {int (* match ) (struct device*,struct device_driver*) ;} ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int stub1 (struct device*,struct device_driver*) ; 
 struct visor_driver* to_visor_driver (struct device_driver*) ; 

__attribute__((used)) static ssize_t typename_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	int i = 0;
	struct bus_type *xbus = dev->bus;
	struct device_driver *xdrv = dev->driver;
	struct visor_driver *drv = NULL;

	if (!xdrv)
		return 0;
	i = xbus->match(dev, xdrv);
	if (!i)
		return 0;
	drv = to_visor_driver(xdrv);
	return sprintf(buf, "%s\n", drv->channel_types[i - 1].name);
}