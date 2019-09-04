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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ev_walk_gpe_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_hw_disable_gpe_block ; 
 int /*<<< orphan*/  hw_disable_all_gpes ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_hw_disable_all_gpes(void)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_disable_all_gpes);

	status = acpi_ev_walk_gpe_list(acpi_hw_disable_gpe_block, NULL);
	return_ACPI_STATUS(status);
}