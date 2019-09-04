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
typedef  int u64 ;
struct iommu_table {scalar_t__ it_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_stack () ; 
 int plpar_tce_put (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static void tce_free_pSeriesLP(struct iommu_table *tbl, long tcenum, long npages)
{
	u64 rc;

	while (npages--) {
		rc = plpar_tce_put((u64)tbl->it_index, (u64)tcenum << 12, 0);

		if (rc && printk_ratelimit()) {
			printk("tce_free_pSeriesLP: plpar_tce_put failed. rc=%lld\n", rc);
			printk("\tindex   = 0x%llx\n", (u64)tbl->it_index);
			printk("\ttcenum  = 0x%llx\n", (u64)tcenum);
			dump_stack();
		}

		tcenum++;
	}
}