#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct driver_data {int /*<<< orphan*/  index; int /*<<< orphan*/ * queue; TYPE_2__* disk; int /*<<< orphan*/  tags; int /*<<< orphan*/  dd_flag; TYPE_1__* pdev; } ;
struct TYPE_5__ {scalar_t__ queue; int /*<<< orphan*/  disk_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_DDF_INIT_DONE_BIT ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_hw_shutdown (struct driver_data*) ; 
 int /*<<< orphan*/  put_disk (TYPE_2__*) ; 
 int /*<<< orphan*/  rssd_index_ida ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtip_block_shutdown(struct driver_data *dd)
{
	mtip_hw_shutdown(dd);

	/* Delete our gendisk structure, and cleanup the blk queue. */
	if (dd->disk) {
		dev_info(&dd->pdev->dev,
			"Shutting down %s ...\n", dd->disk->disk_name);

		if (test_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag))
			del_gendisk(dd->disk);
		if (dd->disk->queue) {
			blk_cleanup_queue(dd->queue);
			blk_mq_free_tag_set(&dd->tags);
		}
		put_disk(dd->disk);
		dd->disk  = NULL;
		dd->queue = NULL;
	}

	ida_free(&rssd_index_ida, dd->index);
	return 0;
}