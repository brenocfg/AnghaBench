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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hsu_dma_chip {int /*<<< orphan*/  irq; int /*<<< orphan*/  offset; int /*<<< orphan*/  length; int /*<<< orphan*/  regs; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HSU_PCI_CHAN_OFFSET ; 
 int /*<<< orphan*/  PCI_IRQ_ALL_TYPES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct hsu_dma_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hsu_dma_probe (struct hsu_dma_chip*) ; 
 int /*<<< orphan*/  hsu_dma_remove (struct hsu_dma_chip*) ; 
 int /*<<< orphan*/  hsu_pci_irq ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct hsu_dma_chip*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_try_set_mwi (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct hsu_dma_chip*) ; 

__attribute__((used)) static int hsu_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct hsu_dma_chip *chip;
	int ret;

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	ret = pcim_iomap_regions(pdev, BIT(0), pci_name(pdev));
	if (ret) {
		dev_err(&pdev->dev, "I/O memory remapping failed\n");
		return ret;
	}

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	chip = devm_kzalloc(&pdev->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	if (ret < 0)
		return ret;

	chip->dev = &pdev->dev;
	chip->regs = pcim_iomap_table(pdev)[0];
	chip->length = pci_resource_len(pdev, 0);
	chip->offset = HSU_PCI_CHAN_OFFSET;
	chip->irq = pci_irq_vector(pdev, 0);

	ret = hsu_dma_probe(chip);
	if (ret)
		return ret;

	ret = request_irq(chip->irq, hsu_pci_irq, 0, "hsu_dma_pci", chip);
	if (ret)
		goto err_register_irq;

	pci_set_drvdata(pdev, chip);

	return 0;

err_register_irq:
	hsu_dma_remove(chip);
	return ret;
}