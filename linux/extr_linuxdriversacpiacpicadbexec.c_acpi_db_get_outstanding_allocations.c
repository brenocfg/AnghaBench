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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

__attribute__((used)) static u32 acpi_db_get_outstanding_allocations(void)
{
	u32 outstanding = 0;

#ifdef ACPI_DBG_TRACK_ALLOCATIONS

	outstanding += acpi_db_get_cache_info(acpi_gbl_state_cache);
	outstanding += acpi_db_get_cache_info(acpi_gbl_ps_node_cache);
	outstanding += acpi_db_get_cache_info(acpi_gbl_ps_node_ext_cache);
	outstanding += acpi_db_get_cache_info(acpi_gbl_operand_cache);
#endif

	return (outstanding);
}