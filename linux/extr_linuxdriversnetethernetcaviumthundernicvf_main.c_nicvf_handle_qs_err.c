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
typedef  int u64 ;
struct queue_set {int cq_cnt; int /*<<< orphan*/ * sq; } ;
struct nicvf {int /*<<< orphan*/  netdev; struct queue_set* qs; } ;

/* Variables and functions */
 int CQ_ERR_MASK ; 
 int /*<<< orphan*/  NICVF_INTR_CQ ; 
 int /*<<< orphan*/  NICVF_INTR_QS_ERR ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_STATUS ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_cmp_queue_config (struct nicvf*,struct queue_set*,int,int) ; 
 int /*<<< orphan*/  nicvf_cq_intr_handler (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_enable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int nicvf_queue_reg_read (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_sq_disable (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_sq_enable (struct nicvf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nicvf_sq_free_used_descs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void nicvf_handle_qs_err(unsigned long data)
{
	struct nicvf *nic = (struct nicvf *)data;
	struct queue_set *qs = nic->qs;
	int qidx;
	u64 status;

	netif_tx_disable(nic->netdev);

	/* Check if it is CQ err */
	for (qidx = 0; qidx < qs->cq_cnt; qidx++) {
		status = nicvf_queue_reg_read(nic, NIC_QSET_CQ_0_7_STATUS,
					      qidx);
		if (!(status & CQ_ERR_MASK))
			continue;
		/* Process already queued CQEs and reconfig CQ */
		nicvf_disable_intr(nic, NICVF_INTR_CQ, qidx);
		nicvf_sq_disable(nic, qidx);
		nicvf_cq_intr_handler(nic->netdev, qidx, NULL, 0);
		nicvf_cmp_queue_config(nic, qs, qidx, true);
		nicvf_sq_free_used_descs(nic->netdev, &qs->sq[qidx], qidx);
		nicvf_sq_enable(nic, &qs->sq[qidx], qidx);

		nicvf_enable_intr(nic, NICVF_INTR_CQ, qidx);
	}

	netif_tx_start_all_queues(nic->netdev);
	/* Re-enable Qset error interrupt */
	nicvf_enable_intr(nic, NICVF_INTR_QS_ERR, 0);
}