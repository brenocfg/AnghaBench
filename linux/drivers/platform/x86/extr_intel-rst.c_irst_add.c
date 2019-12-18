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
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irst_timeout_attr ; 
 int /*<<< orphan*/  irst_wakeup_attr ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int irst_add(struct acpi_device *acpi)
{
	int error;

	error = device_create_file(&acpi->dev, &irst_timeout_attr);
	if (unlikely(error))
		return error;

	error = device_create_file(&acpi->dev, &irst_wakeup_attr);
	if (unlikely(error))
		device_remove_file(&acpi->dev, &irst_timeout_attr);

	return error;
}