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
struct ipack_driver {int /*<<< orphan*/  id_table; } ;
struct ipack_device_id {int dummy; } ;
struct ipack_device {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ipack_device_id* ipack_match_id (int /*<<< orphan*/ ,struct ipack_device*) ; 
 struct ipack_device* to_ipack_dev (struct device*) ; 
 struct ipack_driver* to_ipack_driver (struct device_driver*) ; 

__attribute__((used)) static int ipack_bus_match(struct device *dev, struct device_driver *drv)
{
	struct ipack_device *idev = to_ipack_dev(dev);
	struct ipack_driver *idrv = to_ipack_driver(drv);
	const struct ipack_device_id *found_id;

	found_id = ipack_match_id(idrv->id_table, idev);
	return found_id ? 1 : 0;
}