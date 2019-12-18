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
struct gasket_page_table {scalar_t__ base_slot; scalar_t__ entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  gasket_perform_unmapping (struct gasket_page_table*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ gasket_simple_page_idx (struct gasket_page_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gasket_unmap_simple_pages(struct gasket_page_table *pg_tbl,
				      ulong dev_addr, uint num_pages)
{
	uint slot = gasket_simple_page_idx(pg_tbl, dev_addr);

	gasket_perform_unmapping(pg_tbl, pg_tbl->entries + slot,
				 pg_tbl->base_slot + slot, num_pages, 1);
}