#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct request {TYPE_1__* q; } ;
struct nvme_ns {TYPE_2__* head; TYPE_3__* ctrl; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int status; } ;
struct TYPE_7__ {int /*<<< orphan*/  ana_work; int /*<<< orphan*/  ana_log_buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  requeue_work; int /*<<< orphan*/  requeue_lock; int /*<<< orphan*/  requeue_list; } ;
struct TYPE_5__ {struct nvme_ns* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_NS_ANA_PENDING ; 
#define  NVME_SC_ANA_INACCESSIBLE 131 
#define  NVME_SC_ANA_PERSISTENT_LOSS 130 
#define  NVME_SC_ANA_TRANSITION 129 
#define  NVME_SC_HOST_PATH_ERROR 128 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_steal_bios (int /*<<< orphan*/ *,struct request*) ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_mpath_clear_current_path (struct nvme_ns*) ; 
 TYPE_4__* nvme_req (struct request*) ; 
 int /*<<< orphan*/  nvme_reset_ctrl (TYPE_3__*) ; 
 int /*<<< orphan*/  nvme_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void nvme_failover_req(struct request *req)
{
	struct nvme_ns *ns = req->q->queuedata;
	u16 status = nvme_req(req)->status;
	unsigned long flags;

	spin_lock_irqsave(&ns->head->requeue_lock, flags);
	blk_steal_bios(&ns->head->requeue_list, req);
	spin_unlock_irqrestore(&ns->head->requeue_lock, flags);
	blk_mq_end_request(req, 0);

	switch (status & 0x7ff) {
	case NVME_SC_ANA_TRANSITION:
	case NVME_SC_ANA_INACCESSIBLE:
	case NVME_SC_ANA_PERSISTENT_LOSS:
		/*
		 * If we got back an ANA error we know the controller is alive,
		 * but not ready to serve this namespaces.  The spec suggests
		 * we should update our general state here, but due to the fact
		 * that the admin and I/O queues are not serialized that is
		 * fundamentally racy.  So instead just clear the current path,
		 * mark the the path as pending and kick of a re-read of the ANA
		 * log page ASAP.
		 */
		nvme_mpath_clear_current_path(ns);
		if (ns->ctrl->ana_log_buf) {
			set_bit(NVME_NS_ANA_PENDING, &ns->flags);
			queue_work(nvme_wq, &ns->ctrl->ana_work);
		}
		break;
	case NVME_SC_HOST_PATH_ERROR:
		/*
		 * Temporary transport disruption in talking to the controller.
		 * Try to send on a new path.
		 */
		nvme_mpath_clear_current_path(ns);
		break;
	default:
		/*
		 * Reset the controller for any non-ANA error as we don't know
		 * what caused the error.
		 */
		nvme_reset_ctrl(ns->ctrl);
		break;
	}

	kblockd_schedule_work(&ns->head->requeue_work);
}