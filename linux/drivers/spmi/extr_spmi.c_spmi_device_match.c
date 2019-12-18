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
struct device_driver {scalar_t__ name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_NAME_SIZE ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ of_driver_match_device (struct device*,struct device_driver*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spmi_device_match(struct device *dev, struct device_driver *drv)
{
	if (of_driver_match_device(dev, drv))
		return 1;

	if (drv->name)
		return strncmp(dev_name(dev), drv->name,
			       SPMI_NAME_SIZE) == 0;

	return 0;
}