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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct hclgevf_dev {int num_msi; int num_msi_left; int /*<<< orphan*/ * vector_status; void* vector_irq; scalar_t__ roce_base_msix_offset; scalar_t__ roce_base_vector; scalar_t__ base_msi_vector; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCLGEVF_INVALID_VPORT ; 
 scalar_t__ HNAE3_MIN_VECTOR_NUM ; 
 int PCI_IRQ_MSI ; 
 int PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hnae3_dev_roce_supported (struct hclgevf_dev*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 

__attribute__((used)) static int hclgevf_init_msi(struct hclgevf_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;
	int vectors;
	int i;

	if (hnae3_dev_roce_supported(hdev))
		vectors = pci_alloc_irq_vectors(pdev,
						hdev->roce_base_msix_offset + 1,
						hdev->num_msi,
						PCI_IRQ_MSIX);
	else
		vectors = pci_alloc_irq_vectors(pdev, HNAE3_MIN_VECTOR_NUM,
						hdev->num_msi,
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
		devm_kfree(&pdev->dev, hdev->vector_status);
		pci_free_irq_vectors(pdev);
		return -ENOMEM;
	}

	return 0;
}