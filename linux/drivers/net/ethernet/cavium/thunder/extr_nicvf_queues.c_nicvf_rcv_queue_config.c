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
struct TYPE_3__ {int qs_num; int rq_num; int cfg; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ rq; } ;
typedef  int u64 ;
struct rq_cfg {int ena; scalar_t__ tcp_ena; } ;
struct rcv_queue {int enable; int cq_qs; int cq_idx; int start_rbdr_qs; int start_qs_rbdr_idx; int cont_rbdr_qs; int cont_qs_rbdr_idx; int caching; int /*<<< orphan*/  xdp_rxq; } ;
struct queue_set {int vnic_id; int rbdr_cnt; struct rcv_queue* rq; } ;
struct nicvf {TYPE_2__* netdev; int /*<<< orphan*/  sqs_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_RQ_BP_CFG ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_RQ_CFG ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_RQ_DROP_CFG ; 
 int /*<<< orphan*/  NIC_QSET_RQ_0_7_CFG ; 
 int /*<<< orphan*/  NIC_QSET_RQ_GEN_CFG ; 
 int RQ_DROP_CQ_LVL ; 
 int RQ_DROP_RBDR_LVL ; 
 int RQ_PASS_CQ_LVL ; 
 int RQ_PASS_RBDR_LVL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memset (struct rq_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_config_vlan_stripping (struct nicvf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nicvf_reclaim_rcv_queue (struct nicvf*,struct queue_set*,int) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 
 scalar_t__ xdp_rxq_info_reg (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nicvf_rcv_queue_config(struct nicvf *nic, struct queue_set *qs,
				   int qidx, bool enable)
{
	union nic_mbx mbx = {};
	struct rcv_queue *rq;
	struct rq_cfg rq_cfg;

	rq = &qs->rq[qidx];
	rq->enable = enable;

	/* Disable receive queue */
	nicvf_queue_reg_write(nic, NIC_QSET_RQ_0_7_CFG, qidx, 0);

	if (!rq->enable) {
		nicvf_reclaim_rcv_queue(nic, qs, qidx);
		xdp_rxq_info_unreg(&rq->xdp_rxq);
		return;
	}

	rq->cq_qs = qs->vnic_id;
	rq->cq_idx = qidx;
	rq->start_rbdr_qs = qs->vnic_id;
	rq->start_qs_rbdr_idx = qs->rbdr_cnt - 1;
	rq->cont_rbdr_qs = qs->vnic_id;
	rq->cont_qs_rbdr_idx = qs->rbdr_cnt - 1;
	/* all writes of RBDR data to be loaded into L2 Cache as well*/
	rq->caching = 1;

	/* Driver have no proper error path for failed XDP RX-queue info reg */
	WARN_ON(xdp_rxq_info_reg(&rq->xdp_rxq, nic->netdev, qidx) < 0);

	/* Send a mailbox msg to PF to config RQ */
	mbx.rq.msg = NIC_MBOX_MSG_RQ_CFG;
	mbx.rq.qs_num = qs->vnic_id;
	mbx.rq.rq_num = qidx;
	mbx.rq.cfg = (rq->caching << 26) | (rq->cq_qs << 19) |
			  (rq->cq_idx << 16) | (rq->cont_rbdr_qs << 9) |
			  (rq->cont_qs_rbdr_idx << 8) |
			  (rq->start_rbdr_qs << 1) | (rq->start_qs_rbdr_idx);
	nicvf_send_msg_to_pf(nic, &mbx);

	mbx.rq.msg = NIC_MBOX_MSG_RQ_BP_CFG;
	mbx.rq.cfg = BIT_ULL(63) | BIT_ULL(62) |
		     (RQ_PASS_RBDR_LVL << 16) | (RQ_PASS_CQ_LVL << 8) |
		     (qs->vnic_id << 0);
	nicvf_send_msg_to_pf(nic, &mbx);

	/* RQ drop config
	 * Enable CQ drop to reserve sufficient CQEs for all tx packets
	 */
	mbx.rq.msg = NIC_MBOX_MSG_RQ_DROP_CFG;
	mbx.rq.cfg = BIT_ULL(63) | BIT_ULL(62) |
		     (RQ_PASS_RBDR_LVL << 40) | (RQ_DROP_RBDR_LVL << 32) |
		     (RQ_PASS_CQ_LVL << 16) | (RQ_DROP_CQ_LVL << 8);
	nicvf_send_msg_to_pf(nic, &mbx);

	if (!nic->sqs_mode && (qidx == 0)) {
		/* Enable checking L3/L4 length and TCP/UDP checksums
		 * Also allow IPv6 pkts with zero UDP checksum.
		 */
		nicvf_queue_reg_write(nic, NIC_QSET_RQ_GEN_CFG, 0,
				      (BIT(24) | BIT(23) | BIT(21) | BIT(20)));
		nicvf_config_vlan_stripping(nic, nic->netdev->features);
	}

	/* Enable Receive queue */
	memset(&rq_cfg, 0, sizeof(struct rq_cfg));
	rq_cfg.ena = 1;
	rq_cfg.tcp_ena = 0;
	nicvf_queue_reg_write(nic, NIC_QSET_RQ_0_7_CFG, qidx, *(u64 *)&rq_cfg);
}