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
struct device {int dummy; } ;

/* Variables and functions */
 int __acpi_device_modalias (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  acpi_companion_match (struct device*) ; 

int acpi_device_modalias(struct device *dev, char *buf, int size)
{
	return __acpi_device_modalias(acpi_companion_match(dev), buf, size);
}