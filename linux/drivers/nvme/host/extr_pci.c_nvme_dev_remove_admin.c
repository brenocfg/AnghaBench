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
struct TYPE_2__ {scalar_t__ admin_q; } ;
struct nvme_dev {int /*<<< orphan*/  admin_tagset; TYPE_1__ ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_dying (scalar_t__) ; 

__attribute__((used)) static void nvme_dev_remove_admin(struct nvme_dev *dev)
{
	if (dev->ctrl.admin_q && !blk_queue_dying(dev->ctrl.admin_q)) {
		/*
		 * If the controller was reset during removal, it's possible
		 * user requests may be waiting on a stopped queue. Start the
		 * queue to flush these to completion.
		 */
		blk_mq_unquiesce_queue(dev->ctrl.admin_q);
		blk_cleanup_queue(dev->ctrl.admin_q);
		blk_mq_free_tag_set(&dev->admin_tagset);
	}
}