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
struct dio_driver {struct dio_device_id* id_table; } ;
struct dio_device_id {int dummy; } ;
struct dio_dev {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ dio_match_device (struct dio_device_id const*,struct dio_dev*) ; 
 struct dio_dev* to_dio_dev (struct device*) ; 
 struct dio_driver* to_dio_driver (struct device_driver*) ; 

__attribute__((used)) static int dio_bus_match(struct device *dev, struct device_driver *drv)
{
	struct dio_dev *d = to_dio_dev(dev);
	struct dio_driver *dio_drv = to_dio_driver(drv);
	const struct dio_device_id *ids = dio_drv->id_table;

	if (!ids)
		return 0;

	return dio_match_device(ids, d) ? 1 : 0;
}