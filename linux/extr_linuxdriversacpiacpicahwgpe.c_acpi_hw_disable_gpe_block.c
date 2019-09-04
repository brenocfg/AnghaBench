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
typedef  size_t u32 ;
struct acpi_gpe_xrupt_info {int dummy; } ;
struct acpi_gpe_block_info {size_t register_count; int /*<<< orphan*/ * register_info; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_hw_gpe_enable_write (int,int /*<<< orphan*/ *) ; 

acpi_status
acpi_hw_disable_gpe_block(struct acpi_gpe_xrupt_info *gpe_xrupt_info,
			  struct acpi_gpe_block_info *gpe_block, void *context)
{
	u32 i;
	acpi_status status;

	/* Examine each GPE Register within the block */

	for (i = 0; i < gpe_block->register_count; i++) {

		/* Disable all GPEs in this register */

		status =
		    acpi_hw_gpe_enable_write(0x00,
					     &gpe_block->register_info[i]);
		if (ACPI_FAILURE(status)) {
			return (status);
		}
	}

	return (AE_OK);
}