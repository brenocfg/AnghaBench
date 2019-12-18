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
struct pci_esp_priv {struct esp* esp; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct esp {int /*<<< orphan*/  host; int /*<<< orphan*/  regs; int /*<<< orphan*/  command_block_dma; int /*<<< orphan*/  command_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct esp*) ; 
 int /*<<< orphan*/  kfree (struct pci_esp_priv*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pci_esp_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_esp_unregister (struct esp*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_esp_remove_one(struct pci_dev *pdev)
{
	struct pci_esp_priv *pep = pci_get_drvdata(pdev);
	struct esp *esp = pep->esp;

	scsi_esp_unregister(esp);
	free_irq(pdev->irq, esp);
	pci_set_drvdata(pdev, NULL);
	dma_free_coherent(&pdev->dev, 16, esp->command_block,
			  esp->command_block_dma);
	pci_iounmap(pdev, esp->regs);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kfree(pep);

	scsi_host_put(esp->host);
}