#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ql_tx_buf_cb {int seg_count; TYPE_4__* skb; int /*<<< orphan*/ * map; } ;
struct ql3_adapter {int /*<<< orphan*/  tx_count; TYPE_2__* ndev; int /*<<< orphan*/  pdev; struct ql_tx_buf_cb* tx_buf; } ;
struct ob_mac_iocb_rsp {int flags; size_t transaction_id; } ;
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int OB_MAC_IOCB_RSP_S ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (TYPE_4__*) ; 
 int /*<<< orphan*/  dma_unmap_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_process_mac_tx_intr(struct ql3_adapter *qdev,
				   struct ob_mac_iocb_rsp *mac_rsp)
{
	struct ql_tx_buf_cb *tx_cb;
	int i;

	if (mac_rsp->flags & OB_MAC_IOCB_RSP_S) {
		netdev_warn(qdev->ndev,
			    "Frame too short but it was padded and sent\n");
	}

	tx_cb = &qdev->tx_buf[mac_rsp->transaction_id];

	/*  Check the transmit response flags for any errors */
	if (mac_rsp->flags & OB_MAC_IOCB_RSP_S) {
		netdev_err(qdev->ndev,
			   "Frame too short to be legal, frame not sent\n");

		qdev->ndev->stats.tx_errors++;
		goto frame_not_sent;
	}

	if (tx_cb->seg_count == 0) {
		netdev_err(qdev->ndev, "tx_cb->seg_count == 0: %d\n",
			   mac_rsp->transaction_id);

		qdev->ndev->stats.tx_errors++;
		goto invalid_seg_count;
	}

	pci_unmap_single(qdev->pdev,
			 dma_unmap_addr(&tx_cb->map[0], mapaddr),
			 dma_unmap_len(&tx_cb->map[0], maplen),
			 PCI_DMA_TODEVICE);
	tx_cb->seg_count--;
	if (tx_cb->seg_count) {
		for (i = 1; i < tx_cb->seg_count; i++) {
			pci_unmap_page(qdev->pdev,
				       dma_unmap_addr(&tx_cb->map[i],
						      mapaddr),
				       dma_unmap_len(&tx_cb->map[i], maplen),
				       PCI_DMA_TODEVICE);
		}
	}
	qdev->ndev->stats.tx_packets++;
	qdev->ndev->stats.tx_bytes += tx_cb->skb->len;

frame_not_sent:
	dev_kfree_skb_irq(tx_cb->skb);
	tx_cb->skb = NULL;

invalid_seg_count:
	atomic_inc(&qdev->tx_count);
}