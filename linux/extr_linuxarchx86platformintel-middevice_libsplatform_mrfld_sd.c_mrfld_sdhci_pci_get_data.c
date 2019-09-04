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
struct sdhci_pci_data {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 unsigned int INTEL_MRFLD_SD ; 
 unsigned int PCI_FUNC (int /*<<< orphan*/ ) ; 
 struct sdhci_pci_data mrfld_sdhci_pci_data ; 

__attribute__((used)) static struct sdhci_pci_data *
mrfld_sdhci_pci_get_data(struct pci_dev *pdev, int slotno)
{
	unsigned int func = PCI_FUNC(pdev->devfn);

	if (func == INTEL_MRFLD_SD)
		return &mrfld_sdhci_pci_data;

	return NULL;
}