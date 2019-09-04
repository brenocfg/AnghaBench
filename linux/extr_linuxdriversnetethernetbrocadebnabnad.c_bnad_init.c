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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct bnad {int num_tx; int num_txq_per_tx; int num_rx; int num_rxp_per_rx; int id; int /*<<< orphan*/  bar0; int /*<<< orphan*/  work_q; int /*<<< orphan*/  wq_name; int /*<<< orphan*/  rx_coalescing_timeo; int /*<<< orphan*/  tx_coalescing_timeo; int /*<<< orphan*/  rxq_depth; int /*<<< orphan*/  txq_depth; scalar_t__ msix_num; int /*<<< orphan*/  bna_lock; int /*<<< orphan*/  cfg_flags; scalar_t__ mmio_len; int /*<<< orphan*/  mmio_start; struct pci_dev* pcidev; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_RX_COALESCING_TIMEO ; 
 int /*<<< orphan*/  BFI_TX_COALESCING_TIMEO ; 
 int /*<<< orphan*/  BNAD_CF_DIM_ENABLED ; 
 int /*<<< orphan*/  BNAD_CF_MSIX ; 
 scalar_t__ BNAD_MAILBOX_MSIX_VECTORS ; 
 char* BNAD_NAME ; 
 int /*<<< orphan*/  BNAD_RXQ_DEPTH ; 
 int /*<<< orphan*/  BNAD_TXQ_DEPTH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnad_msix_disable ; 
 int /*<<< orphan*/  bnad_q_num_init (struct bnad*) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int
bnad_init(struct bnad *bnad,
	  struct pci_dev *pdev, struct net_device *netdev)
{
	unsigned long flags;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_drvdata(pdev, netdev);

	bnad->netdev = netdev;
	bnad->pcidev = pdev;
	bnad->mmio_start = pci_resource_start(pdev, 0);
	bnad->mmio_len = pci_resource_len(pdev, 0);
	bnad->bar0 = ioremap_nocache(bnad->mmio_start, bnad->mmio_len);
	if (!bnad->bar0) {
		dev_err(&pdev->dev, "ioremap for bar0 failed\n");
		return -ENOMEM;
	}
	dev_info(&pdev->dev, "bar0 mapped to %p, len %llu\n", bnad->bar0,
		 (unsigned long long) bnad->mmio_len);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	if (!bnad_msix_disable)
		bnad->cfg_flags = BNAD_CF_MSIX;

	bnad->cfg_flags |= BNAD_CF_DIM_ENABLED;

	bnad_q_num_init(bnad);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	bnad->msix_num = (bnad->num_tx * bnad->num_txq_per_tx) +
		(bnad->num_rx * bnad->num_rxp_per_rx) +
			 BNAD_MAILBOX_MSIX_VECTORS;

	bnad->txq_depth = BNAD_TXQ_DEPTH;
	bnad->rxq_depth = BNAD_RXQ_DEPTH;

	bnad->tx_coalescing_timeo = BFI_TX_COALESCING_TIMEO;
	bnad->rx_coalescing_timeo = BFI_RX_COALESCING_TIMEO;

	sprintf(bnad->wq_name, "%s_wq_%d", BNAD_NAME, bnad->id);
	bnad->work_q = create_singlethread_workqueue(bnad->wq_name);
	if (!bnad->work_q) {
		iounmap(bnad->bar0);
		return -ENOMEM;
	}

	return 0;
}