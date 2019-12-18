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
struct ocrdma_mqe {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct ocrdma_dev {TYPE_2__ nic_info; } ;
struct ocrdma_destroy_cq {int bypass_flush_qid; int /*<<< orphan*/  req; } ;
struct ocrdma_cq {int id; int /*<<< orphan*/  pa; int /*<<< orphan*/  va; int /*<<< orphan*/  len; int /*<<< orphan*/  eqn; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_CMD_DELETE_CQ ; 
 int OCRDMA_DESTROY_CQ_QID_MASK ; 
 int OCRDMA_DESTROY_CQ_QID_SHIFT ; 
 int /*<<< orphan*/  OCRDMA_SUBSYS_COMMON ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_destroy_cq*) ; 
 struct ocrdma_destroy_cq* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_init_mch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 
 int /*<<< orphan*/  ocrdma_unbind_eq (struct ocrdma_dev*,int /*<<< orphan*/ ) ; 

void ocrdma_mbx_destroy_cq(struct ocrdma_dev *dev, struct ocrdma_cq *cq)
{
	struct ocrdma_destroy_cq *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DELETE_CQ, sizeof(*cmd));
	if (!cmd)
		return;
	ocrdma_init_mch(&cmd->req, OCRDMA_CMD_DELETE_CQ,
			OCRDMA_SUBSYS_COMMON, sizeof(*cmd));

	cmd->bypass_flush_qid |=
	    (cq->id << OCRDMA_DESTROY_CQ_QID_SHIFT) &
	    OCRDMA_DESTROY_CQ_QID_MASK;

	ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	ocrdma_unbind_eq(dev, cq->eqn);
	dma_free_coherent(&dev->nic_info.pdev->dev, cq->len, cq->va, cq->pa);
	kfree(cmd);
}