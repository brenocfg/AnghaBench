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
struct ptp_qoriq {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int enetc_phc_index ; 
 int /*<<< orphan*/  kfree (struct ptp_qoriq*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 struct ptp_qoriq* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  ptp_qoriq_free (struct ptp_qoriq*) ; 

__attribute__((used)) static void enetc_ptp_remove(struct pci_dev *pdev)
{
	struct ptp_qoriq *ptp_qoriq = pci_get_drvdata(pdev);

	enetc_phc_index = -1;
	ptp_qoriq_free(ptp_qoriq);
	pci_free_irq_vectors(pdev);
	kfree(ptp_qoriq);

	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
}