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
typedef  int /*<<< orphan*/  u64 ;
struct queue_set {int cq_len; struct cmp_queue* cq; } ;
struct nicvf {int dummy; } ;
struct cq_cfg {int ena; scalar_t__ avg_con; int /*<<< orphan*/  qsize; scalar_t__ caching; scalar_t__ reset; } ;
struct TYPE_2__ {scalar_t__ phys_base; } ;
struct cmp_queue {int enable; int /*<<< orphan*/  thresh; TYPE_1__ dmem; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_QUEUE_TIMER_THRESH ; 
 int /*<<< orphan*/  NICVF_CQ_RESET ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_BASE ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_CFG ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_CFG2 ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_THRESH ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  memset (struct cq_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_reclaim_cmp_queue (struct nicvf*,struct queue_set*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void nicvf_cmp_queue_config(struct nicvf *nic, struct queue_set *qs,
			    int qidx, bool enable)
{
	struct cmp_queue *cq;
	struct cq_cfg cq_cfg;

	cq = &qs->cq[qidx];
	cq->enable = enable;

	if (!cq->enable) {
		nicvf_reclaim_cmp_queue(nic, qs, qidx);
		return;
	}

	/* Reset completion queue */
	nicvf_queue_reg_write(nic, NIC_QSET_CQ_0_7_CFG, qidx, NICVF_CQ_RESET);

	if (!cq->enable)
		return;

	spin_lock_init(&cq->lock);
	/* Set completion queue base address */
	nicvf_queue_reg_write(nic, NIC_QSET_CQ_0_7_BASE,
			      qidx, (u64)(cq->dmem.phys_base));

	/* Enable Completion queue */
	memset(&cq_cfg, 0, sizeof(struct cq_cfg));
	cq_cfg.ena = 1;
	cq_cfg.reset = 0;
	cq_cfg.caching = 0;
	cq_cfg.qsize = ilog2(qs->cq_len >> 10);
	cq_cfg.avg_con = 0;
	nicvf_queue_reg_write(nic, NIC_QSET_CQ_0_7_CFG, qidx, *(u64 *)&cq_cfg);

	/* Set threshold value for interrupt generation */
	nicvf_queue_reg_write(nic, NIC_QSET_CQ_0_7_THRESH, qidx, cq->thresh);
	nicvf_queue_reg_write(nic, NIC_QSET_CQ_0_7_CFG2,
			      qidx, CMP_QUEUE_TIMER_THRESH);
}