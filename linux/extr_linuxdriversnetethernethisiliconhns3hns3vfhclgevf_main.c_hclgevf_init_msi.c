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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int irq; int /*<<< orphan*/  dev; } ;
struct hclgevf_dev {int roce_base_msix_offset; int num_msi; int num_msi_left; int base_msi_vector; int roce_base_vector; void* vector_irq; int /*<<< orphan*/ * vector_status; struct pci_dev* pdev; TYPE_1__* ae_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCLGEVF_INVALID_VPORT ; 
 int /*<<< orphan*/  HNAE3_DEV_SUPPORT_ROCE_B ; 
 int PCI_IRQ_MSI ; 
 int PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ hclgevf_dev_ongoing_reset (struct hclgevf_dev*) ; 
 scalar_t__ hnae3_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 

__attribute__((used)) static int hclgevf_init_msi(struct hclgevf_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;
	int vectors;
	int i;

	/* if this is on going reset then skip this initialization */
	if (hclgevf_dev_ongoing_reset(hdev))
		return 0;

	if (hnae3_get_bit(hdev->ae_dev->flag, HNAE3_DEV_SUPPORT_ROCE_B))
		vectors = pci_alloc_irq_vectors(pdev,
						hdev->roce_base_msix_offset + 1,
						hdev->num_msi,
						PCI_IRQ_MSIX);
	else
		vectors = pci_alloc_irq_vectors(pdev, 1, hdev->num_msi,
						PCI_IRQ_MSI | PCI_IRQ_MSIX);

	if (vectors < 0) {
		dev_err(&pdev->dev,
			"failed(%d) to allocate MSI/MSI-X vectors\n",
			vectors);
		return vectors;
	}
	if (vectors < hdev->num_msi)
		dev_warn(&hdev->pdev->dev,
			 "requested %d MSI/MSI-X, but allocated %d MSI/MSI-X\n",
			 hdev->num_msi, vectors);

	hdev->num_msi = vectors;
	hdev->num_msi_left = vectors;
	hdev->base_msi_vector = pdev->irq;
	hdev->roce_base_vector = pdev->irq + hdev->roce_base_msix_offset;

	hdev->vector_status = devm_kcalloc(&pdev->dev, hdev->num_msi,
					   sizeof(u16), GFP_KERNEL);
	if (!hdev->vector_status) {
		pci_free_irq_vectors(pdev);
		return -ENOMEM;
	}

	for (i = 0; i < hdev->num_msi; i++)
		hdev->vector_status[i] = HCLGEVF_INVALID_VPORT;

	hdev->vector_irq = devm_kcalloc(&pdev->dev, hdev->num_msi,
					sizeof(int), GFP_KERNEL);
	if (!hdev->vector_irq) {
		pci_free_irq_vectors(pdev);
		return -ENOMEM;
	}

	return 0;
}