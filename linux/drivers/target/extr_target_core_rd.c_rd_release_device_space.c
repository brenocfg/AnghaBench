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
typedef  scalar_t__ u32 ;
struct rd_dev {int /*<<< orphan*/  sg_table_count; int /*<<< orphan*/ * sg_table_array; int /*<<< orphan*/  rd_dev_id; TYPE_1__* rd_host; } ;
struct TYPE_2__ {int /*<<< orphan*/  rd_host_id; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ rd_release_sgl_table (struct rd_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rd_release_device_space(struct rd_dev *rd_dev)
{
	u32 page_count;

	if (!rd_dev->sg_table_array || !rd_dev->sg_table_count)
		return;

	page_count = rd_release_sgl_table(rd_dev, rd_dev->sg_table_array,
					  rd_dev->sg_table_count);

	pr_debug("CORE_RD[%u] - Released device space for Ramdisk"
		" Device ID: %u, pages %u in %u tables total bytes %lu\n",
		rd_dev->rd_host->rd_host_id, rd_dev->rd_dev_id, page_count,
		rd_dev->sg_table_count, (unsigned long)page_count * PAGE_SIZE);

	rd_dev->sg_table_array = NULL;
	rd_dev->sg_table_count = 0;
}