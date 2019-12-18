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
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct apr_driver {struct apr_device_id* id_table; } ;
struct apr_device_id {scalar_t__ domain_id; scalar_t__ svc_id; } ;
struct apr_device {scalar_t__ domain_id; scalar_t__ svc_id; } ;

/* Variables and functions */
 scalar_t__ of_driver_match_device (struct device*,struct device_driver*) ; 
 struct apr_device* to_apr_device (struct device*) ; 
 struct apr_driver* to_apr_driver (struct device_driver*) ; 

__attribute__((used)) static int apr_device_match(struct device *dev, struct device_driver *drv)
{
	struct apr_device *adev = to_apr_device(dev);
	struct apr_driver *adrv = to_apr_driver(drv);
	const struct apr_device_id *id = adrv->id_table;

	/* Attempt an OF style match first */
	if (of_driver_match_device(dev, drv))
		return 1;

	if (!id)
		return 0;

	while (id->domain_id != 0 || id->svc_id != 0) {
		if (id->domain_id == adev->domain_id &&
		    id->svc_id == adev->svc_id)
			return 1;
		id++;
	}

	return 0;
}