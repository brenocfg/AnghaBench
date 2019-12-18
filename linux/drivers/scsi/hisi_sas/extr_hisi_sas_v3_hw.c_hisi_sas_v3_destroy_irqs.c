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
struct pci_dev {int dummy; } ;
struct hisi_sas_cq {int cq_nvecs; struct hisi_sas_cq* cq; } ;
struct hisi_hba {int cq_nvecs; struct hisi_hba* cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hisi_sas_cq*) ; 
 scalar_t__ hisi_sas_intr_conv ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 

__attribute__((used)) static void
hisi_sas_v3_destroy_irqs(struct pci_dev *pdev, struct hisi_hba *hisi_hba)
{
	int i;

	free_irq(pci_irq_vector(pdev, 1), hisi_hba);
	free_irq(pci_irq_vector(pdev, 2), hisi_hba);
	free_irq(pci_irq_vector(pdev, 11), hisi_hba);
	for (i = 0; i < hisi_hba->cq_nvecs; i++) {
		struct hisi_sas_cq *cq = &hisi_hba->cq[i];
		int nr = hisi_sas_intr_conv ? 16 : 16 + i;

		free_irq(pci_irq_vector(pdev, nr), cq);
	}
	pci_free_irq_vectors(pdev);
}