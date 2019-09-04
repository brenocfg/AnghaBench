#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  max_table_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ROOT_ALLOW_RESIZE ; 
 TYPE_1__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_tb_resize_root_table_list () ; 

acpi_status acpi_allocate_root_table(u32 initial_table_count)
{

	acpi_gbl_root_table_list.max_table_count = initial_table_count;
	acpi_gbl_root_table_list.flags = ACPI_ROOT_ALLOW_RESIZE;

	return (acpi_tb_resize_root_table_list());
}