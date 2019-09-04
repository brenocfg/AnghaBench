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
struct acpi_table_header {int dummy; } ;
struct acpi_pptt_processor {int dummy; } ;

/* Variables and functions */
 int acpi_count_levels (struct acpi_table_header*,struct acpi_pptt_processor*) ; 
 struct acpi_pptt_processor* acpi_find_processor_node (struct acpi_table_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_find_cache_levels(struct acpi_table_header *table_hdr,
				  u32 acpi_cpu_id)
{
	int number_of_levels = 0;
	struct acpi_pptt_processor *cpu;

	cpu = acpi_find_processor_node(table_hdr, acpi_cpu_id);
	if (cpu)
		number_of_levels = acpi_count_levels(table_hdr, cpu);

	return number_of_levels;
}