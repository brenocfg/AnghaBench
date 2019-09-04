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
struct iommu_table {int /*<<< orphan*/  it_size; int /*<<< orphan*/  it_offset; TYPE_1__* it_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear ) (struct iommu_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ is_fadump_active () ; 
 int /*<<< orphan*/  is_kdump_kernel () ; 
 int /*<<< orphan*/  stub1 (struct iommu_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_table_clear(struct iommu_table *tbl)
{
	/*
	 * In case of firmware assisted dump system goes through clean
	 * reboot process at the time of system crash. Hence it's safe to
	 * clear the TCE entries if firmware assisted dump is active.
	 */
	if (!is_kdump_kernel() || is_fadump_active()) {
		/* Clear the table in case firmware left allocations in it */
		tbl->it_ops->clear(tbl, tbl->it_offset, tbl->it_size);
		return;
	}

#ifdef CONFIG_CRASH_DUMP
	if (tbl->it_ops->get) {
		unsigned long index, tceval, tcecount = 0;

		/* Reserve the existing mappings left by the first kernel. */
		for (index = 0; index < tbl->it_size; index++) {
			tceval = tbl->it_ops->get(tbl, index + tbl->it_offset);
			/*
			 * Freed TCE entry contains 0x7fffffffffffffff on JS20
			 */
			if (tceval && (tceval != 0x7fffffffffffffffUL)) {
				__set_bit(index, tbl->it_map);
				tcecount++;
			}
		}

		if ((tbl->it_size - tcecount) < KDUMP_MIN_TCE_ENTRIES) {
			printk(KERN_WARNING "TCE table is full; freeing ");
			printk(KERN_WARNING "%d entries for the kdump boot\n",
				KDUMP_MIN_TCE_ENTRIES);
			for (index = tbl->it_size - KDUMP_MIN_TCE_ENTRIES;
				index < tbl->it_size; index++)
				__clear_bit(index, tbl->it_map);
		}
	}
#endif
}