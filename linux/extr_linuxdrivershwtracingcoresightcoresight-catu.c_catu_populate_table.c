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
struct TYPE_2__ {int* daddrs; } ;
struct tmc_sg_table {int /*<<< orphan*/  dev; TYPE_1__ data_pages; } ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  cate_t ;

/* Variables and functions */
 size_t CATU_LINK_NEXT ; 
 size_t CATU_LINK_PREV ; 
 int CATU_PAGES_PER_SYSPAGE ; 
 unsigned long CATU_PAGE_SIZE ; 
 int CATU_PTRS_PER_PAGE ; 
 unsigned long SZ_1M ; 
 int /*<<< orphan*/  catu_dbg (int /*<<< orphan*/ ,char*,unsigned long,int,int,...) ; 
 int /*<<< orphan*/ * catu_get_table (struct tmc_sg_table*,unsigned long,int*) ; 
 int /*<<< orphan*/  catu_make_entry (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned long tmc_sg_table_buf_size (struct tmc_sg_table*) ; 
 int /*<<< orphan*/  tmc_sg_table_sync_table (struct tmc_sg_table*) ; 

__attribute__((used)) static void
catu_populate_table(struct tmc_sg_table *catu_table)
{
	int i;
	int sys_pidx;	/* Index to current system data page */
	int catu_pidx;	/* Index of CATU page within the system data page */
	unsigned long offset, buf_size, table_end;
	dma_addr_t data_daddr;
	dma_addr_t prev_taddr, next_taddr, cur_taddr;
	cate_t *table_ptr, *next_table;

	buf_size = tmc_sg_table_buf_size(catu_table);
	sys_pidx = catu_pidx = 0;
	offset = 0;

	table_ptr = catu_get_table(catu_table, 0, &cur_taddr);
	prev_taddr = 0;	/* Prev link for the first table */

	while (offset < buf_size) {
		/*
		 * The @offset is always 1M aligned here and we have an
		 * empty table @table_ptr to fill. Each table can address
		 * upto 1MB data buffer. The last table may have fewer
		 * entries if the buffer size is not aligned.
		 */
		table_end = (offset + SZ_1M) < buf_size ?
			    (offset + SZ_1M) : buf_size;
		for (i = 0; offset < table_end;
		     i++, offset += CATU_PAGE_SIZE) {

			data_daddr = catu_table->data_pages.daddrs[sys_pidx] +
				     catu_pidx * CATU_PAGE_SIZE;
			catu_dbg(catu_table->dev,
				"[table %5ld:%03d] 0x%llx\n",
				(offset >> 20), i, data_daddr);
			table_ptr[i] = catu_make_entry(data_daddr);
			/* Move the pointers for data pages */
			catu_pidx = (catu_pidx + 1) % CATU_PAGES_PER_SYSPAGE;
			if (catu_pidx == 0)
				sys_pidx++;
		}

		/*
		 * If we have finished all the valid entries, fill the rest of
		 * the table (i.e, last table page) with invalid entries,
		 * to fail the lookups.
		 */
		if (offset == buf_size) {
			memset(&table_ptr[i], 0,
			       sizeof(cate_t) * (CATU_PTRS_PER_PAGE - i));
			next_taddr = 0;
		} else {
			next_table = catu_get_table(catu_table,
						    offset, &next_taddr);
		}

		table_ptr[CATU_LINK_PREV] = catu_make_entry(prev_taddr);
		table_ptr[CATU_LINK_NEXT] = catu_make_entry(next_taddr);

		catu_dbg(catu_table->dev,
			"[table%5ld]: Cur: 0x%llx Prev: 0x%llx, Next: 0x%llx\n",
			(offset >> 20) - 1,  cur_taddr, prev_taddr, next_taddr);

		/* Update the prev/next addresses */
		if (next_taddr) {
			prev_taddr = cur_taddr;
			cur_taddr = next_taddr;
			table_ptr = next_table;
		}
	}

	/* Sync the table for device */
	tmc_sg_table_sync_table(catu_table);
}