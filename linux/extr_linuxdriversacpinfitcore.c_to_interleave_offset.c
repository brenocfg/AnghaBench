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
typedef  size_t u64 ;
typedef  size_t u32 ;
struct nfit_blk_mmio {size_t line_size; size_t num_lines; size_t table_size; size_t base_offset; struct acpi_nfit_interleave* idt; } ;
struct acpi_nfit_interleave {size_t* line_offset; } ;

/* Variables and functions */
 size_t div_u64_rem (size_t,size_t,size_t*) ; 

__attribute__((used)) static u64 to_interleave_offset(u64 offset, struct nfit_blk_mmio *mmio)
{
	struct acpi_nfit_interleave *idt = mmio->idt;
	u32 sub_line_offset, line_index, line_offset;
	u64 line_no, table_skip_count, table_offset;

	line_no = div_u64_rem(offset, mmio->line_size, &sub_line_offset);
	table_skip_count = div_u64_rem(line_no, mmio->num_lines, &line_index);
	line_offset = idt->line_offset[line_index]
		* mmio->line_size;
	table_offset = table_skip_count * mmio->table_size;

	return mmio->base_offset + line_offset + table_offset + sub_line_offset;
}