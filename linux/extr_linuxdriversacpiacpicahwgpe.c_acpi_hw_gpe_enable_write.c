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
typedef  int /*<<< orphan*/  u8 ;
struct acpi_gpe_register_info {int /*<<< orphan*/  enable_address; int /*<<< orphan*/  enable_mask; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_hw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status
acpi_hw_gpe_enable_write(u8 enable_mask,
			 struct acpi_gpe_register_info *gpe_register_info)
{
	acpi_status status;

	gpe_register_info->enable_mask = enable_mask;

	status = acpi_hw_write(enable_mask, &gpe_register_info->enable_address);
	return (status);
}