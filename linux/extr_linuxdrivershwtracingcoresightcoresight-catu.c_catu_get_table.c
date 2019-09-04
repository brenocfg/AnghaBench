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
struct tmc_pages {int /*<<< orphan*/ * pages; scalar_t__* daddrs; } ;
struct tmc_sg_table {struct tmc_pages table_pages; } ;
typedef  scalar_t__ dma_addr_t ;
typedef  int /*<<< orphan*/  cate_t ;

/* Variables and functions */
 unsigned int CATU_PAGES_PER_SYSPAGE ; 
 unsigned int CATU_PAGE_SIZE ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 unsigned long tmc_sg_table_buf_size (struct tmc_sg_table*) ; 

__attribute__((used)) static inline cate_t *catu_get_table(struct tmc_sg_table *catu_table,
				     unsigned long offset,
				     dma_addr_t *daddrp)
{
	unsigned long buf_size = tmc_sg_table_buf_size(catu_table);
	unsigned int table_nr, pg_idx, pg_offset;
	struct tmc_pages *table_pages = &catu_table->table_pages;
	void *ptr;

	/* Make sure offset is within the range */
	offset %= buf_size;

	/*
	 * Each table can address 1MB and a single kernel page can
	 * contain "CATU_PAGES_PER_SYSPAGE" CATU tables.
	 */
	table_nr = offset >> 20;
	/* Find the table page where the table_nr lies in */
	pg_idx = table_nr / CATU_PAGES_PER_SYSPAGE;
	pg_offset = (table_nr % CATU_PAGES_PER_SYSPAGE) * CATU_PAGE_SIZE;
	if (daddrp)
		*daddrp = table_pages->daddrs[pg_idx] + pg_offset;
	ptr = page_address(table_pages->pages[pg_idx]);
	return (cate_t *)((unsigned long)ptr + pg_offset);
}