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
struct sdhci_pci_chip {int /*<<< orphan*/  pdev; } ;
struct sdhci_host {int /*<<< orphan*/  irq; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_MSI ; 
 int PCI_IRQ_MSI ; 
 int PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int,int,int) ; 
 int pci_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_pci_o2_enable_msi(struct sdhci_pci_chip *chip,
				    struct sdhci_host *host)
{
	int ret;

	ret = pci_find_capability(chip->pdev, PCI_CAP_ID_MSI);
	if (!ret) {
		pr_info("%s: unsupport msi, use INTx irq\n",
			mmc_hostname(host->mmc));
		return;
	}

	ret = pci_alloc_irq_vectors(chip->pdev, 1, 1,
				    PCI_IRQ_MSI | PCI_IRQ_MSIX);
	if (ret < 0) {
		pr_err("%s: enable PCI MSI failed, err=%d\n",
		       mmc_hostname(host->mmc), ret);
		return;
	}

	host->irq = pci_irq_vector(chip->pdev, 0);
}