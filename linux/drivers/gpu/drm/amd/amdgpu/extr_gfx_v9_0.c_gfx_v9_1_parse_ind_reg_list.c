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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void gfx_v9_1_parse_ind_reg_list(int *register_list_format,
				int indirect_offset,
				int list_size,
				int *unique_indirect_regs,
				int unique_indirect_reg_count,
				int *indirect_start_offsets,
				int *indirect_start_offsets_count,
				int max_start_offsets_count)
{
	int idx;

	for (; indirect_offset < list_size; indirect_offset++) {
		WARN_ON(*indirect_start_offsets_count >= max_start_offsets_count);
		indirect_start_offsets[*indirect_start_offsets_count] = indirect_offset;
		*indirect_start_offsets_count = *indirect_start_offsets_count + 1;

		while (register_list_format[indirect_offset] != 0xFFFFFFFF) {
			indirect_offset += 2;

			/* look for the matching indice */
			for (idx = 0; idx < unique_indirect_reg_count; idx++) {
				if (unique_indirect_regs[idx] ==
					register_list_format[indirect_offset] ||
					!unique_indirect_regs[idx])
					break;
			}

			BUG_ON(idx >= unique_indirect_reg_count);

			if (!unique_indirect_regs[idx])
				unique_indirect_regs[idx] = register_list_format[indirect_offset];

			indirect_offset++;
		}
	}
}