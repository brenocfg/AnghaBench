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
typedef  int ulong ;
typedef  scalar_t__ uint ;
struct gasket_page_table {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ gasket_addr_is_simple (struct gasket_page_table*,int) ; 
 int gasket_is_extended_dev_addr_bad (struct gasket_page_table*,int,scalar_t__) ; 
 int gasket_is_simple_dev_addr_bad (struct gasket_page_table*,int,scalar_t__) ; 

bool gasket_page_table_is_dev_addr_bad(struct gasket_page_table *pg_tbl,
				       ulong dev_addr, ulong bytes)
{
	uint num_pages = bytes / PAGE_SIZE;

	if (bytes & (PAGE_SIZE - 1)) {
		dev_err(pg_tbl->device,
			"mapping size 0x%lX must be page aligned\n", bytes);
		return true;
	}

	if (num_pages == 0) {
		dev_err(pg_tbl->device,
			"requested mapping is less than one page: %lu / %lu\n",
			bytes, PAGE_SIZE);
		return true;
	}

	if (gasket_addr_is_simple(pg_tbl, dev_addr))
		return gasket_is_simple_dev_addr_bad(pg_tbl, dev_addr,
						     num_pages);
	return gasket_is_extended_dev_addr_bad(pg_tbl, dev_addr, num_pages);
}