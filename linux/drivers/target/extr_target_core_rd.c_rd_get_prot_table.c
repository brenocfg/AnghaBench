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
typedef  size_t u32 ;
struct scatterlist {int dummy; } ;
struct rd_dev_sg_table {size_t page_start_offset; size_t page_end_offset; } ;
struct rd_dev {size_t sg_prot_count; struct rd_dev_sg_table* sg_prot_array; } ;

/* Variables and functions */
 int RD_MAX_ALLOCATION_SIZE ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 

__attribute__((used)) static struct rd_dev_sg_table *rd_get_prot_table(struct rd_dev *rd_dev, u32 page)
{
	struct rd_dev_sg_table *sg_table;
	u32 i, sg_per_table = (RD_MAX_ALLOCATION_SIZE /
				sizeof(struct scatterlist));

	i = page / sg_per_table;
	if (i < rd_dev->sg_prot_count) {
		sg_table = &rd_dev->sg_prot_array[i];
		if ((sg_table->page_start_offset <= page) &&
		     (sg_table->page_end_offset >= page))
			return sg_table;
	}

	pr_err("Unable to locate struct prot rd_dev_sg_table for page: %u\n",
			page);

	return NULL;
}