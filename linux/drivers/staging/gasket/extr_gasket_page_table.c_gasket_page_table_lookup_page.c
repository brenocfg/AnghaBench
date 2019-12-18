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
typedef  int /*<<< orphan*/  ulong ;
typedef  scalar_t__ uint ;
struct page {int dummy; } ;
struct gasket_page_table_entry {scalar_t__ status; int /*<<< orphan*/  offset; struct page* page; struct gasket_page_table_entry* sublevel; } ;
struct gasket_page_table {scalar_t__ num_simple_entries; scalar_t__ num_extended_entries; int /*<<< orphan*/  mutex; struct gasket_page_table_entry* entries; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PTE_INUSE ; 
 scalar_t__ gasket_addr_is_simple (struct gasket_page_table*,int /*<<< orphan*/ ) ; 
 scalar_t__ gasket_extended_lvl0_page_idx (struct gasket_page_table*,int /*<<< orphan*/ ) ; 
 scalar_t__ gasket_extended_lvl1_page_idx (struct gasket_page_table*,int /*<<< orphan*/ ) ; 
 scalar_t__ gasket_simple_page_idx (struct gasket_page_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int gasket_page_table_lookup_page(struct gasket_page_table *pg_tbl,
				  ulong dev_addr, struct page **ppage,
				  ulong *poffset)
{
	uint page_num;
	struct gasket_page_table_entry *pte;

	mutex_lock(&pg_tbl->mutex);
	if (gasket_addr_is_simple(pg_tbl, dev_addr)) {
		page_num = gasket_simple_page_idx(pg_tbl, dev_addr);
		if (page_num >= pg_tbl->num_simple_entries)
			goto fail;

		pte = pg_tbl->entries + page_num;
		if (pte->status != PTE_INUSE)
			goto fail;
	} else {
		/* Find the level 0 entry, */
		page_num = gasket_extended_lvl0_page_idx(pg_tbl, dev_addr);
		if (page_num >= pg_tbl->num_extended_entries)
			goto fail;

		pte = pg_tbl->entries + pg_tbl->num_simple_entries + page_num;
		if (pte->status != PTE_INUSE)
			goto fail;

		/* and its contained level 1 entry. */
		page_num = gasket_extended_lvl1_page_idx(pg_tbl, dev_addr);
		pte = pte->sublevel + page_num;
		if (pte->status != PTE_INUSE)
			goto fail;
	}

	*ppage = pte->page;
	*poffset = pte->offset;
	mutex_unlock(&pg_tbl->mutex);
	return 0;

fail:
	*ppage = NULL;
	*poffset = 0;
	mutex_unlock(&pg_tbl->mutex);
	return -EINVAL;
}