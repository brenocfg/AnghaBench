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
struct fujitsu_laptop {int /*<<< orphan*/  fifo; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct fujitsu_laptop* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  fujitsu_laptop_platform_remove (struct acpi_device*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_fujitsu_laptop_remove(struct acpi_device *device)
{
	struct fujitsu_laptop *priv = acpi_driver_data(device);

	fujitsu_laptop_platform_remove(device);

	kfifo_free(&priv->fifo);

	return 0;
}