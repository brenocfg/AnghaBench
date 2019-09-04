#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ubiblock {TYPE_1__* gd; int /*<<< orphan*/  tag_set; int /*<<< orphan*/  rq; int /*<<< orphan*/  wq; } ;
struct TYPE_4__ {int /*<<< orphan*/  first_minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_to_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  ubiblock_minor_idr ; 

__attribute__((used)) static void ubiblock_cleanup(struct ubiblock *dev)
{
	/* Stop new requests to arrive */
	del_gendisk(dev->gd);
	/* Flush pending work */
	destroy_workqueue(dev->wq);
	/* Finally destroy the blk queue */
	blk_cleanup_queue(dev->rq);
	blk_mq_free_tag_set(&dev->tag_set);
	dev_info(disk_to_dev(dev->gd), "released");
	idr_remove(&ubiblock_minor_idr, dev->gd->first_minor);
	put_disk(dev->gd);
}