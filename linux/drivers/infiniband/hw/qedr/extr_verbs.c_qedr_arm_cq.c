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
struct qedr_dev {int dummy; } ;
struct qedr_cq {scalar_t__ cq_type; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  arm_flags; scalar_t__ cq_cons; int /*<<< orphan*/  icid; scalar_t__ destroyed; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
typedef  enum ib_cq_notify_flags { ____Placeholder_ib_cq_notify_flags } ib_cq_notify_flags ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,struct qedr_cq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DQ_UCM_ROCE_CQ_ARM_CF_CMD ; 
 int /*<<< orphan*/  DQ_UCM_ROCE_CQ_ARM_SE_CF_CMD ; 
 int EINVAL ; 
 int IB_CQ_NEXT_COMP ; 
 int IB_CQ_SOLICITED ; 
 scalar_t__ QEDR_CQ_TYPE_GSI ; 
 int /*<<< orphan*/  doorbell_cq (struct qedr_cq*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct qedr_cq* get_qedr_cq (struct ib_cq*) ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int qedr_arm_cq(struct ib_cq *ibcq, enum ib_cq_notify_flags flags)
{
	struct qedr_cq *cq = get_qedr_cq(ibcq);
	unsigned long sflags;
	struct qedr_dev *dev;

	dev = get_qedr_dev(ibcq->device);

	if (cq->destroyed) {
		DP_ERR(dev,
		       "warning: arm was invoked after destroy for cq %p (icid=%d)\n",
		       cq, cq->icid);
		return -EINVAL;
	}


	if (cq->cq_type == QEDR_CQ_TYPE_GSI)
		return 0;

	spin_lock_irqsave(&cq->cq_lock, sflags);

	cq->arm_flags = 0;

	if (flags & IB_CQ_SOLICITED)
		cq->arm_flags |= DQ_UCM_ROCE_CQ_ARM_SE_CF_CMD;

	if (flags & IB_CQ_NEXT_COMP)
		cq->arm_flags |= DQ_UCM_ROCE_CQ_ARM_CF_CMD;

	doorbell_cq(cq, cq->cq_cons - 1, cq->arm_flags);

	spin_unlock_irqrestore(&cq->cq_lock, sflags);

	return 0;
}