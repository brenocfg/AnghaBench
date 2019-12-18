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
typedef  size_t u8 ;
struct snd_queue {int /*<<< orphan*/  free_cnt; } ;
struct rcv_queue {int dummy; } ;
struct queue_set {struct rcv_queue* rq; struct snd_queue* sq; struct cmp_queue* cq; } ;
struct nicvf {unsigned int xdp_tx_queues; TYPE_2__* drv_stats; struct nicvf* pnicvf; struct net_device* netdev; scalar_t__ xdp_prog; struct queue_set* qs; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct napi_struct {int dummy; } ;
struct cqe_rx_t {int cqe_type; } ;
struct TYPE_3__ {int q_len; } ;
struct cmp_queue {int /*<<< orphan*/  lock; TYPE_1__ dmem; } ;
struct TYPE_4__ {int /*<<< orphan*/  txq_wake; } ;

/* Variables and functions */
#define  CQE_TYPE_INVALID 133 
#define  CQE_TYPE_RX 132 
#define  CQE_TYPE_RX_SPLIT 131 
#define  CQE_TYPE_RX_TCP 130 
#define  CQE_TYPE_SEND 129 
#define  CQE_TYPE_SEND_PTP 128 
 int CQ_CQE_COUNT ; 
 scalar_t__ GET_CQ_DESC (struct cmp_queue*,int) ; 
 scalar_t__ MIN_SQ_DESC_PER_PKT_XMIT ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_DOOR ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_HEAD ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_STATUS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,unsigned int) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (struct netdev_queue*,unsigned int,unsigned int) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_warn (struct nicvf*,int /*<<< orphan*/ ,struct net_device*,char*,unsigned int) ; 
 unsigned int nicvf_netdev_qidx (struct nicvf*,size_t) ; 
 int /*<<< orphan*/  nicvf_put_sq_desc (struct snd_queue*,int) ; 
 int nicvf_queue_reg_read (struct nicvf*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  nicvf_rcv_pkt_handler (struct net_device*,struct napi_struct*,struct cqe_rx_t*,struct snd_queue*,struct rcv_queue*) ; 
 int /*<<< orphan*/  nicvf_snd_pkt_handler (struct net_device*,void*,int,int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  nicvf_snd_ptp_handler (struct net_device*,void*) ; 
 int /*<<< orphan*/  nicvf_xdp_sq_doorbell (struct nicvf*,struct snd_queue*,size_t) ; 
 int /*<<< orphan*/  prefetch (struct cqe_rx_t*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static int nicvf_cq_intr_handler(struct net_device *netdev, u8 cq_idx,
				 struct napi_struct *napi, int budget)
{
	int processed_cqe, work_done = 0, tx_done = 0;
	int cqe_count, cqe_head;
	int subdesc_cnt = 0;
	struct nicvf *nic = netdev_priv(netdev);
	struct queue_set *qs = nic->qs;
	struct cmp_queue *cq = &qs->cq[cq_idx];
	struct cqe_rx_t *cq_desc;
	struct netdev_queue *txq;
	struct snd_queue *sq = &qs->sq[cq_idx];
	struct rcv_queue *rq = &qs->rq[cq_idx];
	unsigned int tx_pkts = 0, tx_bytes = 0, txq_idx;

	spin_lock_bh(&cq->lock);
loop:
	processed_cqe = 0;
	/* Get no of valid CQ entries to process */
	cqe_count = nicvf_queue_reg_read(nic, NIC_QSET_CQ_0_7_STATUS, cq_idx);
	cqe_count &= CQ_CQE_COUNT;
	if (!cqe_count)
		goto done;

	/* Get head of the valid CQ entries */
	cqe_head = nicvf_queue_reg_read(nic, NIC_QSET_CQ_0_7_HEAD, cq_idx) >> 9;
	cqe_head &= 0xFFFF;

	while (processed_cqe < cqe_count) {
		/* Get the CQ descriptor */
		cq_desc = (struct cqe_rx_t *)GET_CQ_DESC(cq, cqe_head);
		cqe_head++;
		cqe_head &= (cq->dmem.q_len - 1);
		/* Initiate prefetch for next descriptor */
		prefetch((struct cqe_rx_t *)GET_CQ_DESC(cq, cqe_head));

		if ((work_done >= budget) && napi &&
		    (cq_desc->cqe_type != CQE_TYPE_SEND)) {
			break;
		}

		switch (cq_desc->cqe_type) {
		case CQE_TYPE_RX:
			nicvf_rcv_pkt_handler(netdev, napi, cq_desc, sq, rq);
			work_done++;
		break;
		case CQE_TYPE_SEND:
			nicvf_snd_pkt_handler(netdev, (void *)cq_desc,
					      budget, &subdesc_cnt,
					      &tx_pkts, &tx_bytes);
			tx_done++;
		break;
		case CQE_TYPE_SEND_PTP:
			nicvf_snd_ptp_handler(netdev, (void *)cq_desc);
		break;
		case CQE_TYPE_INVALID:
		case CQE_TYPE_RX_SPLIT:
		case CQE_TYPE_RX_TCP:
			/* Ignore for now */
		break;
		}
		processed_cqe++;
	}

	/* Ring doorbell to inform H/W to reuse processed CQEs */
	nicvf_queue_reg_write(nic, NIC_QSET_CQ_0_7_DOOR,
			      cq_idx, processed_cqe);

	if ((work_done < budget) && napi)
		goto loop;

done:
	/* Update SQ's descriptor free count */
	if (subdesc_cnt)
		nicvf_put_sq_desc(sq, subdesc_cnt);

	txq_idx = nicvf_netdev_qidx(nic, cq_idx);
	/* Handle XDP TX queues */
	if (nic->pnicvf->xdp_prog) {
		if (txq_idx < nic->pnicvf->xdp_tx_queues) {
			nicvf_xdp_sq_doorbell(nic, sq, cq_idx);
			goto out;
		}
		nic = nic->pnicvf;
		txq_idx -= nic->pnicvf->xdp_tx_queues;
	}

	/* Wakeup TXQ if its stopped earlier due to SQ full */
	if (tx_done ||
	    (atomic_read(&sq->free_cnt) >= MIN_SQ_DESC_PER_PKT_XMIT)) {
		netdev = nic->pnicvf->netdev;
		txq = netdev_get_tx_queue(netdev, txq_idx);
		if (tx_pkts)
			netdev_tx_completed_queue(txq, tx_pkts, tx_bytes);

		/* To read updated queue and carrier status */
		smp_mb();
		if (netif_tx_queue_stopped(txq) && netif_carrier_ok(netdev)) {
			netif_tx_wake_queue(txq);
			nic = nic->pnicvf;
			this_cpu_inc(nic->drv_stats->txq_wake);
			netif_warn(nic, tx_err, netdev,
				   "Transmit queue wakeup SQ%d\n", txq_idx);
		}
	}

out:
	spin_unlock_bh(&cq->lock);
	return work_done;
}