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
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct rd_dev_sg_table {int dummy; } ;
struct rd_dev {scalar_t__ rd_page_count; int rd_flags; int sg_table_count; int /*<<< orphan*/  rd_dev_id; TYPE_1__* rd_host; struct rd_dev_sg_table* sg_table_array; } ;
struct TYPE_2__ {int /*<<< orphan*/  rd_host_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RDF_NULLIO ; 
 int RD_MAX_ALLOCATION_SIZE ; 
 struct rd_dev_sg_table* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int rd_allocate_sgl_table (struct rd_dev*,struct rd_dev_sg_table*,int,int) ; 

__attribute__((used)) static int rd_build_device_space(struct rd_dev *rd_dev)
{
	struct rd_dev_sg_table *sg_table;
	u32 sg_tables, total_sg_needed;
	u32 max_sg_per_table = (RD_MAX_ALLOCATION_SIZE /
				sizeof(struct scatterlist));
	int rc;

	if (rd_dev->rd_page_count <= 0) {
		pr_err("Illegal page count: %u for Ramdisk device\n",
		       rd_dev->rd_page_count);
		return -EINVAL;
	}

	/* Don't need backing pages for NULLIO */
	if (rd_dev->rd_flags & RDF_NULLIO)
		return 0;

	total_sg_needed = rd_dev->rd_page_count;

	sg_tables = (total_sg_needed / max_sg_per_table) + 1;
	sg_table = kcalloc(sg_tables, sizeof(*sg_table), GFP_KERNEL);
	if (!sg_table)
		return -ENOMEM;

	rd_dev->sg_table_array = sg_table;
	rd_dev->sg_table_count = sg_tables;

	rc = rd_allocate_sgl_table(rd_dev, sg_table, total_sg_needed, 0x00);
	if (rc)
		return rc;

	pr_debug("CORE_RD[%u] - Built Ramdisk Device ID: %u space of"
		 " %u pages in %u tables\n", rd_dev->rd_host->rd_host_id,
		 rd_dev->rd_dev_id, rd_dev->rd_page_count,
		 rd_dev->sg_table_count);

	return 0;
}