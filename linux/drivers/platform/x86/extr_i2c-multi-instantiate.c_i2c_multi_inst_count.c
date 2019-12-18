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
struct acpi_resource_i2c_serialbus {int dummy; } ;
struct acpi_resource {int dummy; } ;

/* Variables and functions */
 scalar_t__ i2c_acpi_get_i2c_resource (struct acpi_resource*,struct acpi_resource_i2c_serialbus**) ; 

__attribute__((used)) static int i2c_multi_inst_count(struct acpi_resource *ares, void *data)
{
	struct acpi_resource_i2c_serialbus *sb;
	int *count = data;

	if (i2c_acpi_get_i2c_resource(ares, &sb))
		*count = *count + 1;

	return 1;
}