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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct eni_zero {int /*<<< orphan*/  dma; int /*<<< orphan*/  addr; } ;
struct eni_dev {struct eni_zero zero; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 struct eni_dev* ENI_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  ENI_ZEROES_SIZE ; 
 int /*<<< orphan*/  atm_dev_deregister (struct atm_dev*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eni_do_release (struct atm_dev*) ; 
 int /*<<< orphan*/  kfree (struct eni_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct atm_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void eni_remove_one(struct pci_dev *pdev)
{
	struct atm_dev *dev = pci_get_drvdata(pdev);
	struct eni_dev *ed = ENI_DEV(dev);
	struct eni_zero *zero = &ed->zero;

	eni_do_release(dev);
	atm_dev_deregister(dev);
	dma_free_coherent(&pdev->dev, ENI_ZEROES_SIZE, zero->addr, zero->dma);
	kfree(ed);
	pci_disable_device(pdev);
}