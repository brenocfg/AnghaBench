#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvmefc_ls_req {scalar_t__ rsplen; scalar_t__ rqstlen; int /*<<< orphan*/  rqstdma; } ;
struct nvmefc_ls_req_op {int req_queued; int /*<<< orphan*/  lsreq_list; struct nvmefc_ls_req ls_req; struct nvme_fc_rport* rport; } ;
struct nvme_fc_rport {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  fc_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_fc_rport_put (struct nvme_fc_rport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
__nvme_fc_finish_ls_req(struct nvmefc_ls_req_op *lsop)
{
	struct nvme_fc_rport *rport = lsop->rport;
	struct nvmefc_ls_req *lsreq = &lsop->ls_req;
	unsigned long flags;

	spin_lock_irqsave(&rport->lock, flags);

	if (!lsop->req_queued) {
		spin_unlock_irqrestore(&rport->lock, flags);
		return;
	}

	list_del(&lsop->lsreq_list);

	lsop->req_queued = false;

	spin_unlock_irqrestore(&rport->lock, flags);

	fc_dma_unmap_single(rport->dev, lsreq->rqstdma,
				  (lsreq->rqstlen + lsreq->rsplen),
				  DMA_BIDIRECTIONAL);

	nvme_fc_rport_put(rport);
}