#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int intr_idx; } ;
struct vmxnet3_rx_queue {char* name; int qid; int qid2; int dataRingQid; TYPE_3__ comp_ring; int /*<<< orphan*/  dev; } ;
struct vmxnet3_intr {scalar_t__ type; char* event_msi_vector_name; int event_intr_idx; int num_intrs; int /*<<< orphan*/  mask_mode; int /*<<< orphan*/ * mod_levels; TYPE_2__* msix_entries; } ;
struct vmxnet3_adapter {int num_tx_queues; scalar_t__ share_intr; int num_rx_queues; struct vmxnet3_rx_queue* netdev; struct vmxnet3_rx_queue* rx_queue; struct vmxnet3_rx_queue* tx_queue; struct vmxnet3_intr intr; TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  UPT1_IML_ADAPTIVE ; 
 scalar_t__ VMXNET3_INTR_BUDDYSHARE ; 
 scalar_t__ VMXNET3_INTR_TXSHARE ; 
 scalar_t__ VMXNET3_IT_MSI ; 
 scalar_t__ VMXNET3_IT_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  netdev_err (struct vmxnet3_rx_queue*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  netdev_info (struct vmxnet3_rx_queue*,char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vmxnet3_rx_queue*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  vmxnet3_intr ; 
 int /*<<< orphan*/  vmxnet3_msix_event ; 
 int /*<<< orphan*/  vmxnet3_msix_rx ; 
 int /*<<< orphan*/  vmxnet3_msix_tx ; 

__attribute__((used)) static int
vmxnet3_request_irqs(struct vmxnet3_adapter *adapter)
{
	struct vmxnet3_intr *intr = &adapter->intr;
	int err = 0, i;
	int vector = 0;

#ifdef CONFIG_PCI_MSI
	if (adapter->intr.type == VMXNET3_IT_MSIX) {
		for (i = 0; i < adapter->num_tx_queues; i++) {
			if (adapter->share_intr != VMXNET3_INTR_BUDDYSHARE) {
				sprintf(adapter->tx_queue[i].name, "%s-tx-%d",
					adapter->netdev->name, vector);
				err = request_irq(
					      intr->msix_entries[vector].vector,
					      vmxnet3_msix_tx, 0,
					      adapter->tx_queue[i].name,
					      &adapter->tx_queue[i]);
			} else {
				sprintf(adapter->tx_queue[i].name, "%s-rxtx-%d",
					adapter->netdev->name, vector);
			}
			if (err) {
				dev_err(&adapter->netdev->dev,
					"Failed to request irq for MSIX, %s, "
					"error %d\n",
					adapter->tx_queue[i].name, err);
				return err;
			}

			/* Handle the case where only 1 MSIx was allocated for
			 * all tx queues */
			if (adapter->share_intr == VMXNET3_INTR_TXSHARE) {
				for (; i < adapter->num_tx_queues; i++)
					adapter->tx_queue[i].comp_ring.intr_idx
								= vector;
				vector++;
				break;
			} else {
				adapter->tx_queue[i].comp_ring.intr_idx
								= vector++;
			}
		}
		if (adapter->share_intr == VMXNET3_INTR_BUDDYSHARE)
			vector = 0;

		for (i = 0; i < adapter->num_rx_queues; i++) {
			if (adapter->share_intr != VMXNET3_INTR_BUDDYSHARE)
				sprintf(adapter->rx_queue[i].name, "%s-rx-%d",
					adapter->netdev->name, vector);
			else
				sprintf(adapter->rx_queue[i].name, "%s-rxtx-%d",
					adapter->netdev->name, vector);
			err = request_irq(intr->msix_entries[vector].vector,
					  vmxnet3_msix_rx, 0,
					  adapter->rx_queue[i].name,
					  &(adapter->rx_queue[i]));
			if (err) {
				netdev_err(adapter->netdev,
					   "Failed to request irq for MSIX, "
					   "%s, error %d\n",
					   adapter->rx_queue[i].name, err);
				return err;
			}

			adapter->rx_queue[i].comp_ring.intr_idx = vector++;
		}

		sprintf(intr->event_msi_vector_name, "%s-event-%d",
			adapter->netdev->name, vector);
		err = request_irq(intr->msix_entries[vector].vector,
				  vmxnet3_msix_event, 0,
				  intr->event_msi_vector_name, adapter->netdev);
		intr->event_intr_idx = vector;

	} else if (intr->type == VMXNET3_IT_MSI) {
		adapter->num_rx_queues = 1;
		err = request_irq(adapter->pdev->irq, vmxnet3_intr, 0,
				  adapter->netdev->name, adapter->netdev);
	} else {
#endif
		adapter->num_rx_queues = 1;
		err = request_irq(adapter->pdev->irq, vmxnet3_intr,
				  IRQF_SHARED, adapter->netdev->name,
				  adapter->netdev);
#ifdef CONFIG_PCI_MSI
	}
#endif
	intr->num_intrs = vector + 1;
	if (err) {
		netdev_err(adapter->netdev,
			   "Failed to request irq (intr type:%d), error %d\n",
			   intr->type, err);
	} else {
		/* Number of rx queues will not change after this */
		for (i = 0; i < adapter->num_rx_queues; i++) {
			struct vmxnet3_rx_queue *rq = &adapter->rx_queue[i];
			rq->qid = i;
			rq->qid2 = i + adapter->num_rx_queues;
			rq->dataRingQid = i + 2 * adapter->num_rx_queues;
		}

		/* init our intr settings */
		for (i = 0; i < intr->num_intrs; i++)
			intr->mod_levels[i] = UPT1_IML_ADAPTIVE;
		if (adapter->intr.type != VMXNET3_IT_MSIX) {
			adapter->intr.event_intr_idx = 0;
			for (i = 0; i < adapter->num_tx_queues; i++)
				adapter->tx_queue[i].comp_ring.intr_idx = 0;
			adapter->rx_queue[0].comp_ring.intr_idx = 0;
		}

		netdev_info(adapter->netdev,
			    "intr type %u, mode %u, %u vectors allocated\n",
			    intr->type, intr->mask_mode, intr->num_intrs);
	}

	return err;
}