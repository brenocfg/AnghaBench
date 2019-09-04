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
struct toshsd_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  ioaddr; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct toshsd_host*) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct toshsd_host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toshsd_powerdown (struct toshsd_host*) ; 

__attribute__((used)) static void toshsd_remove(struct pci_dev *pdev)
{
	struct toshsd_host *host = pci_get_drvdata(pdev);

	mmc_remove_host(host->mmc);
	toshsd_powerdown(host);
	free_irq(pdev->irq, host);
	pci_iounmap(pdev, host->ioaddr);
	pci_release_regions(pdev);
	mmc_free_host(host->mmc);
	pci_set_drvdata(pdev, NULL);
	pci_disable_device(pdev);
}