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
struct resource {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_get_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct resource*,void**) ; 
 int /*<<< orphan*/  acpi_res_consumer_cb ; 

struct acpi_device *acpi_resource_consumer(struct resource *res)
{
	struct acpi_device *consumer = NULL;

	acpi_get_devices(NULL, acpi_res_consumer_cb, res, (void **) &consumer);
	return consumer;
}