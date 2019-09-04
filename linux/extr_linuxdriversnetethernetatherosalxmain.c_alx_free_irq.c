#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ msix_enabled; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct alx_priv {int num_napi; struct alx_priv** qnapi; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct alx_priv*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 

__attribute__((used)) static void alx_free_irq(struct alx_priv *alx)
{
	struct pci_dev *pdev = alx->hw.pdev;
	int i;

	free_irq(pci_irq_vector(pdev, 0), alx);
	if (alx->hw.pdev->msix_enabled) {
		for (i = 0; i < alx->num_napi; i++)
			free_irq(pci_irq_vector(pdev, i + 1), alx->qnapi[i]);
	}

	pci_free_irq_vectors(pdev);
}