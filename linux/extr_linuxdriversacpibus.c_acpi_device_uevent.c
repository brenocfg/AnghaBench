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
 int __acpi_device_uevent_modalias (int /*<<< orphan*/ ,struct kobj_uevent_env*) ; 
 int /*<<< orphan*/  to_acpi_device (struct device*) ; 

__attribute__((used)) static int acpi_device_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	return __acpi_device_uevent_modalias(to_acpi_device(dev), env);
}