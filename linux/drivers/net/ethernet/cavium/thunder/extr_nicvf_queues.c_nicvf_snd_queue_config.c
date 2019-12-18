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
struct TYPE_3__ {int qs_num; int sq_num; int cfg; int /*<<< orphan*/  sqs_mode; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ sq; } ;
typedef  int /*<<< orphan*/  u64 ;
struct sq_cfg {int ena; int cq_limit; scalar_t__ tstmp_bgx_intf; int /*<<< orphan*/  qsize; scalar_t__ ldwb; scalar_t__ reset; } ;
struct TYPE_4__ {scalar_t__ phys_base; } ;
struct snd_queue {int enable; int cq_qs; int cq_idx; int /*<<< orphan*/  affinity_mask; int /*<<< orphan*/  thresh; TYPE_2__ dmem; } ;
struct queue_set {int vnic_id; int sq_len; int cq_len; struct snd_queue* sq; } ;
struct nicvf {int /*<<< orphan*/  netdev; int /*<<< orphan*/  sqs_mode; } ;

/* Variables and functions */
 int CMP_QUEUE_PIPELINE_RSVD ; 
 int /*<<< orphan*/  NICVF_SQ_RESET ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_SQ_CFG ; 
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_BASE ; 
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_CFG ; 
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_THRESH ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  memset (struct sq_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_set_xps_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_reclaim_snd_queue (struct nicvf*,struct queue_set*,int) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static void nicvf_snd_queue_config(struct nicvf *nic, struct queue_set *qs,
				   int qidx, bool enable)
{
	union nic_mbx mbx = {};
	struct snd_queue *sq;
	struct sq_cfg sq_cfg;

	sq = &qs->sq[qidx];
	sq->enable = enable;

	if (!sq->enable) {
		nicvf_reclaim_snd_queue(nic, qs, qidx);
		return;
	}

	/* Reset send queue */
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_CFG, qidx, NICVF_SQ_RESET);

	sq->cq_qs = qs->vnic_id;
	sq->cq_idx = qidx;

	/* Send a mailbox msg to PF to config SQ */
	mbx.sq.msg = NIC_MBOX_MSG_SQ_CFG;
	mbx.sq.qs_num = qs->vnic_id;
	mbx.sq.sq_num = qidx;
	mbx.sq.sqs_mode = nic->sqs_mode;
	mbx.sq.cfg = (sq->cq_qs << 3) | sq->cq_idx;
	nicvf_send_msg_to_pf(nic, &mbx);

	/* Set queue base address */
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_BASE,
			      qidx, (u64)(sq->dmem.phys_base));

	/* Enable send queue  & set queue size */
	memset(&sq_cfg, 0, sizeof(struct sq_cfg));
	sq_cfg.ena = 1;
	sq_cfg.reset = 0;
	sq_cfg.ldwb = 0;
	sq_cfg.qsize = ilog2(qs->sq_len >> 10);
	sq_cfg.tstmp_bgx_intf = 0;
	/* CQ's level at which HW will stop processing SQEs to avoid
	 * transmitting a pkt with no space in CQ to post CQE_TX.
	 */
	sq_cfg.cq_limit = (CMP_QUEUE_PIPELINE_RSVD * 256) / qs->cq_len;
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_CFG, qidx, *(u64 *)&sq_cfg);

	/* Set threshold value for interrupt generation */
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_THRESH, qidx, sq->thresh);

	/* Set queue:cpu affinity for better load distribution */
	if (cpu_online(qidx)) {
		cpumask_set_cpu(qidx, &sq->affinity_mask);
		netif_set_xps_queue(nic->netdev,
				    &sq->affinity_mask, qidx);
	}
}