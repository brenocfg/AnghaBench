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
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;
struct pvrdma_cmd_destroy_cq {size_t cq_handle; TYPE_1__ hdr; } ;
union pvrdma_cmd_req {struct pvrdma_cmd_destroy_cq destroy_cq; } ;
struct pvrdma_dev {int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  cq_tbl_lock; int /*<<< orphan*/ ** cq_tbl; TYPE_2__* pdev; } ;
struct pvrdma_cq {size_t cq_handle; } ;
struct ib_udata {int dummy; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVRDMA_CMD_DESTROY_CQ ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct pvrdma_cmd_destroy_cq*,int /*<<< orphan*/ ,int) ; 
 int pvrdma_cmd_post (struct pvrdma_dev*,union pvrdma_cmd_req*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_free_cq (struct pvrdma_dev*,struct pvrdma_cq*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pvrdma_cq* to_vcq (struct ib_cq*) ; 
 struct pvrdma_dev* to_vdev (int /*<<< orphan*/ ) ; 

void pvrdma_destroy_cq(struct ib_cq *cq, struct ib_udata *udata)
{
	struct pvrdma_cq *vcq = to_vcq(cq);
	union pvrdma_cmd_req req;
	struct pvrdma_cmd_destroy_cq *cmd = &req.destroy_cq;
	struct pvrdma_dev *dev = to_vdev(cq->device);
	unsigned long flags;
	int ret;

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_DESTROY_CQ;
	cmd->cq_handle = vcq->cq_handle;

	ret = pvrdma_cmd_post(dev, &req, NULL, 0);
	if (ret < 0)
		dev_warn(&dev->pdev->dev,
			 "could not destroy completion queue, error: %d\n",
			 ret);

	/* free cq's resources */
	spin_lock_irqsave(&dev->cq_tbl_lock, flags);
	dev->cq_tbl[vcq->cq_handle] = NULL;
	spin_unlock_irqrestore(&dev->cq_tbl_lock, flags);

	pvrdma_free_cq(dev, vcq);
	atomic_dec(&dev->num_cqs);
}