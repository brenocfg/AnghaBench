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
struct toshsd_host {int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  lock; struct pci_dev* pdev; struct mmc_host* mmc; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct mmc_host {int f_min; int f_max; int /*<<< orphan*/  ocr_avail; int /*<<< orphan*/  caps; int /*<<< orphan*/ * ops; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int HCLK ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  MMC_CAP_4_BIT_DATA ; 
 int /*<<< orphan*/  MMC_VDD_32_33 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct toshsd_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct toshsd_host*) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (int /*<<< orphan*/ *,int) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct toshsd_host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toshsd_init (struct toshsd_host*) ; 
 int /*<<< orphan*/  toshsd_irq ; 
 int /*<<< orphan*/  toshsd_ops ; 
 int /*<<< orphan*/  toshsd_thread_irq ; 

__attribute__((used)) static int toshsd_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int ret;
	struct toshsd_host *host;
	struct mmc_host *mmc;
	resource_size_t base;

	ret = pci_enable_device(pdev);
	if (ret)
		return ret;

	mmc = mmc_alloc_host(sizeof(struct toshsd_host), &pdev->dev);
	if (!mmc) {
		ret = -ENOMEM;
		goto err;
	}

	host = mmc_priv(mmc);
	host->mmc = mmc;

	host->pdev = pdev;
	pci_set_drvdata(pdev, host);

	ret = pci_request_regions(pdev, DRIVER_NAME);
	if (ret)
		goto free;

	host->ioaddr = pci_iomap(pdev, 0, 0);
	if (!host->ioaddr) {
		ret = -ENOMEM;
		goto release;
	}

	/* Set MMC host parameters */
	mmc->ops = &toshsd_ops;
	mmc->caps = MMC_CAP_4_BIT_DATA;
	mmc->ocr_avail = MMC_VDD_32_33;

	mmc->f_min = HCLK / 512;
	mmc->f_max = HCLK;

	spin_lock_init(&host->lock);

	toshsd_init(host);

	ret = request_threaded_irq(pdev->irq, toshsd_irq, toshsd_thread_irq,
				   IRQF_SHARED, DRIVER_NAME, host);
	if (ret)
		goto unmap;

	mmc_add_host(mmc);

	base = pci_resource_start(pdev, 0);
	dev_dbg(&pdev->dev, "MMIO %pa, IRQ %d\n", &base, pdev->irq);

	pm_suspend_ignore_children(&pdev->dev, 1);

	return 0;

unmap:
	pci_iounmap(pdev, host->ioaddr);
release:
	pci_release_regions(pdev);
free:
	mmc_free_host(mmc);
	pci_set_drvdata(pdev, NULL);
err:
	pci_disable_device(pdev);
	return ret;
}