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
struct tb_nhi_ops {int (* init ) (struct tb_nhi*) ;} ;
struct tb_nhi {int hop_count; struct pci_dev* pdev; struct tb_nhi_ops const* ops; int /*<<< orphan*/  lock; void* rx_rings; void* tx_rings; scalar_t__ iobase; } ;
struct tb {int dummy; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ REG_HOP_COUNT ; 
 int /*<<< orphan*/  TB_AUTOSUSPEND_DELAY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct tb_nhi* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tb* icm_probe (struct tb_nhi*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  nhi_imr_valid (struct pci_dev*) ; 
 int nhi_init_msi (struct tb_nhi*) ; 
 int /*<<< orphan*/  nhi_shutdown (struct tb_nhi*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct tb*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int,char*) ; 
 scalar_t__* pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct tb_nhi*) ; 
 int tb_domain_add (struct tb*) ; 
 int /*<<< orphan*/  tb_domain_put (struct tb*) ; 
 struct tb* tb_probe (struct tb_nhi*) ; 

__attribute__((used)) static int nhi_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct tb_nhi *nhi;
	struct tb *tb;
	int res;

	if (!nhi_imr_valid(pdev)) {
		dev_warn(&pdev->dev, "firmware image not valid, aborting\n");
		return -ENODEV;
	}

	res = pcim_enable_device(pdev);
	if (res) {
		dev_err(&pdev->dev, "cannot enable PCI device, aborting\n");
		return res;
	}

	res = pcim_iomap_regions(pdev, 1 << 0, "thunderbolt");
	if (res) {
		dev_err(&pdev->dev, "cannot obtain PCI resources, aborting\n");
		return res;
	}

	nhi = devm_kzalloc(&pdev->dev, sizeof(*nhi), GFP_KERNEL);
	if (!nhi)
		return -ENOMEM;

	nhi->pdev = pdev;
	nhi->ops = (const struct tb_nhi_ops *)id->driver_data;
	/* cannot fail - table is allocated bin pcim_iomap_regions */
	nhi->iobase = pcim_iomap_table(pdev)[0];
	nhi->hop_count = ioread32(nhi->iobase + REG_HOP_COUNT) & 0x3ff;
	if (nhi->hop_count != 12 && nhi->hop_count != 32)
		dev_warn(&pdev->dev, "unexpected hop count: %d\n",
			 nhi->hop_count);

	nhi->tx_rings = devm_kcalloc(&pdev->dev, nhi->hop_count,
				     sizeof(*nhi->tx_rings), GFP_KERNEL);
	nhi->rx_rings = devm_kcalloc(&pdev->dev, nhi->hop_count,
				     sizeof(*nhi->rx_rings), GFP_KERNEL);
	if (!nhi->tx_rings || !nhi->rx_rings)
		return -ENOMEM;

	res = nhi_init_msi(nhi);
	if (res) {
		dev_err(&pdev->dev, "cannot enable MSI, aborting\n");
		return res;
	}

	spin_lock_init(&nhi->lock);

	res = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (res)
		res = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (res) {
		dev_err(&pdev->dev, "failed to set DMA mask\n");
		return res;
	}

	pci_set_master(pdev);

	if (nhi->ops && nhi->ops->init) {
		res = nhi->ops->init(nhi);
		if (res)
			return res;
	}

	tb = icm_probe(nhi);
	if (!tb)
		tb = tb_probe(nhi);
	if (!tb) {
		dev_err(&nhi->pdev->dev,
			"failed to determine connection manager, aborting\n");
		return -ENODEV;
	}

	dev_dbg(&nhi->pdev->dev, "NHI initialized, starting thunderbolt\n");

	res = tb_domain_add(tb);
	if (res) {
		/*
		 * At this point the RX/TX rings might already have been
		 * activated. Do a proper shutdown.
		 */
		tb_domain_put(tb);
		nhi_shutdown(nhi);
		return res;
	}
	pci_set_drvdata(pdev, tb);

	pm_runtime_allow(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, TB_AUTOSUSPEND_DELAY);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_put_autosuspend(&pdev->dev);

	return 0;
}