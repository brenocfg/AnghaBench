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
typedef  int u32 ;

/* Variables and functions */
 int ACPI_LV_TABLES ; 
 int acpi_dbg_layer ; 
 int acpi_dbg_level ; 
 int /*<<< orphan*/  acpi_ut_dump_buffer (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

void
acpi_ut_debug_dump_buffer(u8 *buffer, u32 count, u32 display, u32 component_id)
{

	/* Only dump the buffer if tracing is enabled */

	if (!((ACPI_LV_TABLES & acpi_dbg_level) &&
	      (component_id & acpi_dbg_layer))) {
		return;
	}

	acpi_ut_dump_buffer(buffer, count, display, 0);
}