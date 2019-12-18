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
typedef  int /*<<< orphan*/  uint ;
struct gasket_page_table {scalar_t__ entries; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  gasket_is_pte_range_free (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gasket_simple_page_idx (struct gasket_page_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gasket_alloc_simple_entries(struct gasket_page_table *pg_tbl,
				       ulong dev_addr, uint num_pages)
{
	if (!gasket_is_pte_range_free(pg_tbl->entries +
				      gasket_simple_page_idx(pg_tbl, dev_addr),
				      num_pages))
		return -EBUSY;

	return 0;
}