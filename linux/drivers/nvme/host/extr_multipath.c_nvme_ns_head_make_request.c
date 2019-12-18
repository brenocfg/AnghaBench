#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {struct nvme_ns_head* queuedata; } ;
struct nvme_ns_head {int /*<<< orphan*/  srcu; int /*<<< orphan*/  requeue_lock; int /*<<< orphan*/  requeue_list; int /*<<< orphan*/  disk; } ;
struct nvme_ns {TYPE_2__* head; TYPE_1__* disk; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_status; TYPE_3__ bi_iter; TYPE_1__* bi_disk; int /*<<< orphan*/  bi_opf; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_5__ {int /*<<< orphan*/  disk; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  REQ_NVME_MPATH ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  blk_queue_split (struct request_queue*,struct bio**) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (struct device*,char*) ; 
 int /*<<< orphan*/  direct_make_request (struct bio*) ; 
 int /*<<< orphan*/  disk_devt (int /*<<< orphan*/ ) ; 
 struct device* disk_to_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct nvme_ns*) ; 
 scalar_t__ nvme_available_path (struct nvme_ns_head*) ; 
 struct nvme_ns* nvme_find_path (struct nvme_ns_head*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_block_bio_remap (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_qc_t nvme_ns_head_make_request(struct request_queue *q,
		struct bio *bio)
{
	struct nvme_ns_head *head = q->queuedata;
	struct device *dev = disk_to_dev(head->disk);
	struct nvme_ns *ns;
	blk_qc_t ret = BLK_QC_T_NONE;
	int srcu_idx;

	/*
	 * The namespace might be going away and the bio might
	 * be moved to a different queue via blk_steal_bios(),
	 * so we need to use the bio_split pool from the original
	 * queue to allocate the bvecs from.
	 */
	blk_queue_split(q, &bio);

	srcu_idx = srcu_read_lock(&head->srcu);
	ns = nvme_find_path(head);
	if (likely(ns)) {
		bio->bi_disk = ns->disk;
		bio->bi_opf |= REQ_NVME_MPATH;
		trace_block_bio_remap(bio->bi_disk->queue, bio,
				      disk_devt(ns->head->disk),
				      bio->bi_iter.bi_sector);
		ret = direct_make_request(bio);
	} else if (nvme_available_path(head)) {
		dev_warn_ratelimited(dev, "no usable path - requeuing I/O\n");

		spin_lock_irq(&head->requeue_lock);
		bio_list_add(&head->requeue_list, bio);
		spin_unlock_irq(&head->requeue_lock);
	} else {
		dev_warn_ratelimited(dev, "no available path - failing I/O\n");

		bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
	}

	srcu_read_unlock(&head->srcu, srcu_idx);
	return ret;
}