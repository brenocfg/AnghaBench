#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  limits; struct nvme_ns_head* queuedata; } ;
struct nvme_ns_head {int instance; TYPE_2__* disk; int /*<<< orphan*/  requeue_work; int /*<<< orphan*/  requeue_lock; int /*<<< orphan*/  requeue_list; int /*<<< orphan*/  lock; } ;
struct nvme_ctrl {int vwc; TYPE_1__* subsys; int /*<<< orphan*/  numa_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk_name; int /*<<< orphan*/  flags; struct request_queue* queue; struct nvme_ns_head* private_data; int /*<<< orphan*/ * fops; } ;
struct TYPE_3__ {int cmic; int instance; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GENHD_FL_EXT_DEVT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NVME_CTRL_VWC_PRESENT ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 TYPE_2__* alloc_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 struct request_queue* blk_alloc_queue_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_make_request (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_write_cache (struct request_queue*,int,int) ; 
 int /*<<< orphan*/  blk_set_stacking_limits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multipath ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_ns_head_make_request ; 
 int /*<<< orphan*/  nvme_ns_head_ops ; 
 int /*<<< orphan*/  nvme_requeue_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 

int nvme_mpath_alloc_disk(struct nvme_ctrl *ctrl, struct nvme_ns_head *head)
{
	struct request_queue *q;
	bool vwc = false;

	mutex_init(&head->lock);
	bio_list_init(&head->requeue_list);
	spin_lock_init(&head->requeue_lock);
	INIT_WORK(&head->requeue_work, nvme_requeue_work);

	/*
	 * Add a multipath node if the subsystems supports multiple controllers.
	 * We also do this for private namespaces as the namespace sharing data could
	 * change after a rescan.
	 */
	if (!(ctrl->subsys->cmic & (1 << 1)) || !multipath)
		return 0;

	q = blk_alloc_queue_node(GFP_KERNEL, ctrl->numa_node);
	if (!q)
		goto out;
	q->queuedata = head;
	blk_queue_make_request(q, nvme_ns_head_make_request);
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	/* set to a default value for 512 until disk is validated */
	blk_queue_logical_block_size(q, 512);
	blk_set_stacking_limits(&q->limits);

	/* we need to propagate up the VMC settings */
	if (ctrl->vwc & NVME_CTRL_VWC_PRESENT)
		vwc = true;
	blk_queue_write_cache(q, vwc, vwc);

	head->disk = alloc_disk(0);
	if (!head->disk)
		goto out_cleanup_queue;
	head->disk->fops = &nvme_ns_head_ops;
	head->disk->private_data = head;
	head->disk->queue = q;
	head->disk->flags = GENHD_FL_EXT_DEVT;
	sprintf(head->disk->disk_name, "nvme%dn%d",
			ctrl->subsys->instance, head->instance);
	return 0;

out_cleanup_queue:
	blk_cleanup_queue(q);
out:
	return -ENOMEM;
}