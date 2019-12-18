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
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int acpi_device_uevent_modalias (struct device*,struct kobj_uevent_env*) ; 
 int of_device_uevent_modalias (struct device*,struct kobj_uevent_env*) ; 

__attribute__((used)) static int serdev_device_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	int rc;

	/* TODO: platform modalias */

	rc = acpi_device_uevent_modalias(dev, env);
	if (rc != -ENODEV)
		return rc;

	return of_device_uevent_modalias(dev, env);
}