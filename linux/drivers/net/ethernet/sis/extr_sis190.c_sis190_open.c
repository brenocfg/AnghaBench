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
struct sis190_private {int /*<<< orphan*/  tx_dma; void* TxDescRing; int /*<<< orphan*/  rx_dma; void* RxDescRing; struct pci_dev* pci_dev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  RX_RING_BYTES ; 
 int /*<<< orphan*/  TX_RING_BYTES ; 
 struct sis190_private* netdev_priv (struct net_device*) ; 
 void* pci_alloc_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  sis190_delete_timer (struct net_device*) ; 
 int /*<<< orphan*/  sis190_hw_start (struct net_device*) ; 
 int sis190_init_ring (struct net_device*) ; 
 int /*<<< orphan*/  sis190_irq ; 
 int /*<<< orphan*/  sis190_request_timer (struct net_device*) ; 
 int /*<<< orphan*/  sis190_rx_clear (struct sis190_private*) ; 
 int /*<<< orphan*/  sis190_set_rxbufsize (struct sis190_private*,struct net_device*) ; 

__attribute__((used)) static int sis190_open(struct net_device *dev)
{
	struct sis190_private *tp = netdev_priv(dev);
	struct pci_dev *pdev = tp->pci_dev;
	int rc = -ENOMEM;

	sis190_set_rxbufsize(tp, dev);

	/*
	 * Rx and Tx descriptors need 256 bytes alignment.
	 * pci_alloc_consistent() guarantees a stronger alignment.
	 */
	tp->TxDescRing = pci_alloc_consistent(pdev, TX_RING_BYTES, &tp->tx_dma);
	if (!tp->TxDescRing)
		goto out;

	tp->RxDescRing = pci_alloc_consistent(pdev, RX_RING_BYTES, &tp->rx_dma);
	if (!tp->RxDescRing)
		goto err_free_tx_0;

	rc = sis190_init_ring(dev);
	if (rc < 0)
		goto err_free_rx_1;

	sis190_request_timer(dev);

	rc = request_irq(pdev->irq, sis190_irq, IRQF_SHARED, dev->name, dev);
	if (rc < 0)
		goto err_release_timer_2;

	sis190_hw_start(dev);
out:
	return rc;

err_release_timer_2:
	sis190_delete_timer(dev);
	sis190_rx_clear(tp);
err_free_rx_1:
	pci_free_consistent(pdev, RX_RING_BYTES, tp->RxDescRing, tp->rx_dma);
err_free_tx_0:
	pci_free_consistent(pdev, TX_RING_BYTES, tp->TxDescRing, tp->tx_dma);
	goto out;
}