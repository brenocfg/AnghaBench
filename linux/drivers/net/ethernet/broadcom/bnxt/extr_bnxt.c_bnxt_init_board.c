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
struct bnxt {int /*<<< orphan*/  state; int /*<<< orphan*/  current_interval; int /*<<< orphan*/  timer; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  db_lock; int /*<<< orphan*/  ntp_fltr_lock; int /*<<< orphan*/  fw_reset_task; int /*<<< orphan*/  sp_task; void* bar2; void* bar1; void* bar0; struct pci_dev* pdev; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_DEFAULT_RX_RING_SIZE ; 
 int /*<<< orphan*/  BNXT_DEFAULT_TX_RING_SIZE ; 
 int /*<<< orphan*/  BNXT_STATE_OPEN ; 
 int /*<<< orphan*/  BNXT_TIMER_INTERVAL ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_MODULE_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_fw_reset_task ; 
 int /*<<< orphan*/  bnxt_init_dflt_coal (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_sp_task ; 
 int /*<<< orphan*/  bnxt_timer ; 
 int /*<<< orphan*/  bnxt_unmap_bars (struct bnxt*,struct pci_dev*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 void* pci_ioremap_bar (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_init_board(struct pci_dev *pdev, struct net_device *dev)
{
	int rc;
	struct bnxt *bp = netdev_priv(dev);

	SET_NETDEV_DEV(dev, &pdev->dev);

	/* enable device (incl. PCI PM wakeup), and bus-mastering */
	rc = pci_enable_device(pdev);
	if (rc) {
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		goto init_err;
	}

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
		dev_err(&pdev->dev,
			"Cannot find PCI device base address, aborting\n");
		rc = -ENODEV;
		goto init_err_disable;
	}

	rc = pci_request_regions(pdev, DRV_MODULE_NAME);
	if (rc) {
		dev_err(&pdev->dev, "Cannot obtain PCI resources, aborting\n");
		goto init_err_disable;
	}

	if (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64)) != 0 &&
	    dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)) != 0) {
		dev_err(&pdev->dev, "System does not support DMA, aborting\n");
		goto init_err_disable;
	}

	pci_set_master(pdev);

	bp->dev = dev;
	bp->pdev = pdev;

	bp->bar0 = pci_ioremap_bar(pdev, 0);
	if (!bp->bar0) {
		dev_err(&pdev->dev, "Cannot map device registers, aborting\n");
		rc = -ENOMEM;
		goto init_err_release;
	}

	bp->bar1 = pci_ioremap_bar(pdev, 2);
	if (!bp->bar1) {
		dev_err(&pdev->dev, "Cannot map doorbell registers, aborting\n");
		rc = -ENOMEM;
		goto init_err_release;
	}

	bp->bar2 = pci_ioremap_bar(pdev, 4);
	if (!bp->bar2) {
		dev_err(&pdev->dev, "Cannot map bar4 registers, aborting\n");
		rc = -ENOMEM;
		goto init_err_release;
	}

	pci_enable_pcie_error_reporting(pdev);

	INIT_WORK(&bp->sp_task, bnxt_sp_task);
	INIT_DELAYED_WORK(&bp->fw_reset_task, bnxt_fw_reset_task);

	spin_lock_init(&bp->ntp_fltr_lock);
#if BITS_PER_LONG == 32
	spin_lock_init(&bp->db_lock);
#endif

	bp->rx_ring_size = BNXT_DEFAULT_RX_RING_SIZE;
	bp->tx_ring_size = BNXT_DEFAULT_TX_RING_SIZE;

	bnxt_init_dflt_coal(bp);

	timer_setup(&bp->timer, bnxt_timer, 0);
	bp->current_interval = BNXT_TIMER_INTERVAL;

	clear_bit(BNXT_STATE_OPEN, &bp->state);
	return 0;

init_err_release:
	bnxt_unmap_bars(bp, pdev);
	pci_release_regions(pdev);

init_err_disable:
	pci_disable_device(pdev);

init_err:
	return rc;
}