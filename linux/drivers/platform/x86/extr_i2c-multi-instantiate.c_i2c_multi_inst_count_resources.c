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
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dev_free_resource_list (int /*<<< orphan*/ *) ; 
 int acpi_dev_get_resources (struct acpi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  i2c_multi_inst_count ; 
 int /*<<< orphan*/  r ; 

__attribute__((used)) static int i2c_multi_inst_count_resources(struct acpi_device *adev)
{
	LIST_HEAD(r);
	int count = 0;
	int ret;

	ret = acpi_dev_get_resources(adev, &r, i2c_multi_inst_count, &count);
	if (ret < 0)
		return ret;

	acpi_dev_free_resource_list(&r);
	return count;
}