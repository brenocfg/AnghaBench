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
struct rbd_device {TYPE_1__* disk; int /*<<< orphan*/  tag_set; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 

__attribute__((used)) static void rbd_free_disk(struct rbd_device *rbd_dev)
{
	blk_cleanup_queue(rbd_dev->disk->queue);
	blk_mq_free_tag_set(&rbd_dev->tag_set);
	put_disk(rbd_dev->disk);
	rbd_dev->disk = NULL;
}