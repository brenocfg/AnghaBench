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
struct switch_ctx {unsigned long region_entries_per_slot_bits; int region_entries_per_slot; unsigned int region_table_entry_bits; } ;

/* Variables and functions */

__attribute__((used)) static void switch_get_position(struct switch_ctx *sctx, unsigned long region_nr,
				unsigned long *region_index, unsigned *bit)
{
	if (sctx->region_entries_per_slot_bits >= 0) {
		*region_index = region_nr >> sctx->region_entries_per_slot_bits;
		*bit = region_nr & (sctx->region_entries_per_slot - 1);
	} else {
		*region_index = region_nr / sctx->region_entries_per_slot;
		*bit = region_nr % sctx->region_entries_per_slot;
	}

	*bit *= sctx->region_table_entry_bits;
}