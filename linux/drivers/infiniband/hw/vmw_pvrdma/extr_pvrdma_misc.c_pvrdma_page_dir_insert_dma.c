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
typedef  scalar_t__ u64 ;
struct pvrdma_page_dir {scalar_t__ npages; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t PVRDMA_PAGE_DIR_PAGE (scalar_t__) ; 
 scalar_t__* pvrdma_page_dir_table (struct pvrdma_page_dir*,scalar_t__) ; 

int pvrdma_page_dir_insert_dma(struct pvrdma_page_dir *pdir, u64 idx,
			       dma_addr_t daddr)
{
	u64 *table;

	if (idx >= pdir->npages)
		return -EINVAL;

	table = pvrdma_page_dir_table(pdir, idx);
	table[PVRDMA_PAGE_DIR_PAGE(idx)] = daddr;

	return 0;
}