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
struct gasket_page_table {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ gasket_addr_is_simple (struct gasket_page_table*,int /*<<< orphan*/ ) ; 
 int gasket_map_extended_pages (struct gasket_page_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gasket_map_simple_pages (struct gasket_page_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int gasket_page_table_map(struct gasket_page_table *pg_tbl, ulong host_addr,
			  ulong dev_addr, uint num_pages)
{
	int ret;

	if (!num_pages)
		return 0;

	mutex_lock(&pg_tbl->mutex);

	if (gasket_addr_is_simple(pg_tbl, dev_addr)) {
		ret = gasket_map_simple_pages(pg_tbl, host_addr, dev_addr,
					      num_pages);
	} else {
		ret = gasket_map_extended_pages(pg_tbl, host_addr, dev_addr,
						num_pages);
	}

	mutex_unlock(&pg_tbl->mutex);
	return ret;
}