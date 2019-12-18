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
struct pci_dev {int dummy; } ;
struct kvaser_pciefd {scalar_t__ reg_base; TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ KVASER_PCIEFD_IEN_REG ; 
 int /*<<< orphan*/  KVASER_PCIEFD_IRQ_ALL_MSK ; 
 scalar_t__ KVASER_PCIEFD_IRQ_REG ; 
 scalar_t__ KVASER_PCIEFD_SRB_CTRL_REG ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct kvaser_pciefd*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kvaser_pciefd_remove_all_ctrls (struct kvaser_pciefd*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct kvaser_pciefd* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void kvaser_pciefd_remove(struct pci_dev *pdev)
{
	struct kvaser_pciefd *pcie = pci_get_drvdata(pdev);

	kvaser_pciefd_remove_all_ctrls(pcie);

	/* Turn off IRQ generation */
	iowrite32(0, pcie->reg_base + KVASER_PCIEFD_SRB_CTRL_REG);
	iowrite32(KVASER_PCIEFD_IRQ_ALL_MSK,
		  pcie->reg_base + KVASER_PCIEFD_IRQ_REG);
	iowrite32(0, pcie->reg_base + KVASER_PCIEFD_IEN_REG);

	free_irq(pcie->pci->irq, pcie);

	pci_clear_master(pdev);
	pci_iounmap(pdev, pcie->reg_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}