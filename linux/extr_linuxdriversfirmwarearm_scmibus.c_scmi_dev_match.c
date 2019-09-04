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
struct scmi_driver {int dummy; } ;
struct scmi_device_id {int dummy; } ;
struct scmi_device {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scmi_device_id* scmi_dev_match_id (struct scmi_device*,struct scmi_driver*) ; 
 struct scmi_device* to_scmi_dev (struct device*) ; 
 struct scmi_driver* to_scmi_driver (struct device_driver*) ; 

__attribute__((used)) static int scmi_dev_match(struct device *dev, struct device_driver *drv)
{
	struct scmi_driver *scmi_drv = to_scmi_driver(drv);
	struct scmi_device *scmi_dev = to_scmi_dev(dev);
	const struct scmi_device_id *id;

	id = scmi_dev_match_id(scmi_dev, scmi_drv);
	if (id)
		return 1;

	return 0;
}