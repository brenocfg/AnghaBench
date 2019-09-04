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
struct list_head {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_NAME__DMA ; 
 int __acpi_dev_get_resources (struct acpi_device*,struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_memory ; 

int acpi_dev_get_dma_resources(struct acpi_device *adev, struct list_head *list)
{
	return __acpi_dev_get_resources(adev, list, is_memory, NULL,
					METHOD_NAME__DMA);
}