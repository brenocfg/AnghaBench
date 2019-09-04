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
struct switch_ctx {int region_size; int region_size_bits; int region_table_entry_bits; int region_entries_per_slot; int region_entries_per_slot_bits; int nr_regions; int /*<<< orphan*/  region_table; } ;
struct dm_target {int len; char* error; struct switch_ctx* private; } ;
typedef  int sector_t ;
typedef  int region_table_slot_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ULONG_MAX ; 
 void* __ffs (int) ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 scalar_t__ sector_div (int,int) ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_region_table(struct dm_target *ti, unsigned nr_paths)
{
	struct switch_ctx *sctx = ti->private;
	sector_t nr_regions = ti->len;
	sector_t nr_slots;

	if (!(sctx->region_size & (sctx->region_size - 1)))
		sctx->region_size_bits = __ffs(sctx->region_size);
	else
		sctx->region_size_bits = -1;

	sctx->region_table_entry_bits = 1;
	while (sctx->region_table_entry_bits < sizeof(region_table_slot_t) * 8 &&
	       (region_table_slot_t)1 << sctx->region_table_entry_bits < nr_paths)
		sctx->region_table_entry_bits++;

	sctx->region_entries_per_slot = (sizeof(region_table_slot_t) * 8) / sctx->region_table_entry_bits;
	if (!(sctx->region_entries_per_slot & (sctx->region_entries_per_slot - 1)))
		sctx->region_entries_per_slot_bits = __ffs(sctx->region_entries_per_slot);
	else
		sctx->region_entries_per_slot_bits = -1;

	if (sector_div(nr_regions, sctx->region_size))
		nr_regions++;

	if (nr_regions >= ULONG_MAX) {
		ti->error = "Region table too large";
		return -EINVAL;
	}
	sctx->nr_regions = nr_regions;

	nr_slots = nr_regions;
	if (sector_div(nr_slots, sctx->region_entries_per_slot))
		nr_slots++;

	if (nr_slots > ULONG_MAX / sizeof(region_table_slot_t)) {
		ti->error = "Region table too large";
		return -EINVAL;
	}

	sctx->region_table = vmalloc(array_size(nr_slots,
						sizeof(region_table_slot_t)));
	if (!sctx->region_table) {
		ti->error = "Cannot allocate region table";
		return -ENOMEM;
	}

	return 0;
}