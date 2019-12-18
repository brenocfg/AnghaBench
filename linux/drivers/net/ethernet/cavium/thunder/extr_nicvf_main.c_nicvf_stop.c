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
struct TYPE_3__ {int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ msg; } ;
struct queue_set {int rbdr_cnt; int cq_cnt; } ;
struct nicvf_cq_poll {int /*<<< orphan*/  napi; } ;
struct nicvf {int link_up; int sqs_count; int num_vec; struct nicvf* pnicvf; int /*<<< orphan*/ * ptp_skb; struct nicvf_cq_poll** napi; struct queue_set* qs; int /*<<< orphan*/  rbdr_work; scalar_t__ rb_work_scheduled; int /*<<< orphan*/  qs_err_task; int /*<<< orphan*/  rbdr_task; int /*<<< orphan*/  pdev; TYPE_2__** snicvf; int /*<<< orphan*/  sqs_mode; int /*<<< orphan*/  netdev; scalar_t__ nicvf_rx_mode_wq; int /*<<< orphan*/  link_change_work; } ;
struct net_device {int num_tx_queues; } ;
struct TYPE_4__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NICVF_INTR_CQ ; 
 int /*<<< orphan*/  NICVF_INTR_MBOX ; 
 int /*<<< orphan*/  NICVF_INTR_QS_ERR ; 
 int /*<<< orphan*/  NICVF_INTR_RBDR ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_SHUTDOWN ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_clear_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_config_data_transfer (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_free_cq_poll (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_qset_config (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 
 int /*<<< orphan*/  nicvf_unregister_interrupts (struct nicvf*) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

int nicvf_stop(struct net_device *netdev)
{
	int irq, qidx;
	struct nicvf *nic = netdev_priv(netdev);
	struct queue_set *qs = nic->qs;
	struct nicvf_cq_poll *cq_poll = NULL;
	union nic_mbx mbx = {};

	/* wait till all queued set_rx_mode tasks completes */
	if (nic->nicvf_rx_mode_wq) {
		cancel_delayed_work_sync(&nic->link_change_work);
		drain_workqueue(nic->nicvf_rx_mode_wq);
	}

	mbx.msg.msg = NIC_MBOX_MSG_SHUTDOWN;
	nicvf_send_msg_to_pf(nic, &mbx);

	netif_carrier_off(netdev);
	netif_tx_stop_all_queues(nic->netdev);
	nic->link_up = false;

	/* Teardown secondary qsets first */
	if (!nic->sqs_mode) {
		for (qidx = 0; qidx < nic->sqs_count; qidx++) {
			if (!nic->snicvf[qidx])
				continue;
			nicvf_stop(nic->snicvf[qidx]->netdev);
			nic->snicvf[qidx] = NULL;
		}
	}

	/* Disable RBDR & QS error interrupts */
	for (qidx = 0; qidx < qs->rbdr_cnt; qidx++) {
		nicvf_disable_intr(nic, NICVF_INTR_RBDR, qidx);
		nicvf_clear_intr(nic, NICVF_INTR_RBDR, qidx);
	}
	nicvf_disable_intr(nic, NICVF_INTR_QS_ERR, 0);
	nicvf_clear_intr(nic, NICVF_INTR_QS_ERR, 0);

	/* Wait for pending IRQ handlers to finish */
	for (irq = 0; irq < nic->num_vec; irq++)
		synchronize_irq(pci_irq_vector(nic->pdev, irq));

	tasklet_kill(&nic->rbdr_task);
	tasklet_kill(&nic->qs_err_task);
	if (nic->rb_work_scheduled)
		cancel_delayed_work_sync(&nic->rbdr_work);

	for (qidx = 0; qidx < nic->qs->cq_cnt; qidx++) {
		cq_poll = nic->napi[qidx];
		if (!cq_poll)
			continue;
		napi_synchronize(&cq_poll->napi);
		/* CQ intr is enabled while napi_complete,
		 * so disable it now
		 */
		nicvf_disable_intr(nic, NICVF_INTR_CQ, qidx);
		nicvf_clear_intr(nic, NICVF_INTR_CQ, qidx);
		napi_disable(&cq_poll->napi);
		netif_napi_del(&cq_poll->napi);
	}

	netif_tx_disable(netdev);

	for (qidx = 0; qidx < netdev->num_tx_queues; qidx++)
		netdev_tx_reset_queue(netdev_get_tx_queue(netdev, qidx));

	/* Free resources */
	nicvf_config_data_transfer(nic, false);

	/* Disable HW Qset */
	nicvf_qset_config(nic, false);

	/* disable mailbox interrupt */
	nicvf_disable_intr(nic, NICVF_INTR_MBOX, 0);

	nicvf_unregister_interrupts(nic);

	nicvf_free_cq_poll(nic);

	/* Free any pending SKB saved to receive timestamp */
	if (nic->ptp_skb) {
		dev_kfree_skb_any(nic->ptp_skb);
		nic->ptp_skb = NULL;
	}

	/* Clear multiqset info */
	nic->pnicvf = nic;

	return 0;
}