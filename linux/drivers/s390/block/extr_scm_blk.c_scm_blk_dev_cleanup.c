#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scm_blk_dev {TYPE_1__* gendisk; int /*<<< orphan*/  tag_set; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 

void scm_blk_dev_cleanup(struct scm_blk_dev *bdev)
{
	del_gendisk(bdev->gendisk);
	blk_cleanup_queue(bdev->gendisk->queue);
	blk_mq_free_tag_set(&bdev->tag_set);
	put_disk(bdev->gendisk);
}