#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  teardown_irq; int /*<<< orphan*/  setup_irq; struct device* dev; } ;
struct tegra_msi {int irq; int /*<<< orphan*/  domain; TYPE_2__ chip; int /*<<< orphan*/  virt; int /*<<< orphan*/  phys; int /*<<< orphan*/  lock; } ;
struct tegra_pcie {struct device* dev; struct tegra_msi msi; } ;
struct platform_device {int dummy; } ;
struct pci_host_bridge {TYPE_2__* msi; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NO_KERNEL_MAPPING ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_PCI_MSI_NR ; 
 int /*<<< orphan*/  IRQF_NO_THREAD ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_attrs (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_set_coherent_mask (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct tegra_pcie*) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_domain_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct pci_host_bridge* pci_host_bridge_from_priv (struct tegra_pcie*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_pcie*) ; 
 TYPE_1__ tegra_msi_irq_chip ; 
 int /*<<< orphan*/  tegra_msi_setup_irq ; 
 int /*<<< orphan*/  tegra_msi_teardown_irq ; 
 int /*<<< orphan*/  tegra_pcie_msi_irq ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int tegra_pcie_msi_setup(struct tegra_pcie *pcie)
{
	struct pci_host_bridge *host = pci_host_bridge_from_priv(pcie);
	struct platform_device *pdev = to_platform_device(pcie->dev);
	struct tegra_msi *msi = &pcie->msi;
	struct device *dev = pcie->dev;
	int err;

	mutex_init(&msi->lock);

	msi->chip.dev = dev;
	msi->chip.setup_irq = tegra_msi_setup_irq;
	msi->chip.teardown_irq = tegra_msi_teardown_irq;

	msi->domain = irq_domain_add_linear(dev->of_node, INT_PCI_MSI_NR,
					    &msi_domain_ops, &msi->chip);
	if (!msi->domain) {
		dev_err(dev, "failed to create IRQ domain\n");
		return -ENOMEM;
	}

	err = platform_get_irq_byname(pdev, "msi");
	if (err < 0) {
		dev_err(dev, "failed to get IRQ: %d\n", err);
		goto free_irq_domain;
	}

	msi->irq = err;

	err = request_irq(msi->irq, tegra_pcie_msi_irq, IRQF_NO_THREAD,
			  tegra_msi_irq_chip.name, pcie);
	if (err < 0) {
		dev_err(dev, "failed to request IRQ: %d\n", err);
		goto free_irq_domain;
	}

	/* Though the PCIe controller can address >32-bit address space, to
	 * facilitate endpoints that support only 32-bit MSI target address,
	 * the mask is set to 32-bit to make sure that MSI target address is
	 * always a 32-bit address
	 */
	err = dma_set_coherent_mask(dev, DMA_BIT_MASK(32));
	if (err < 0) {
		dev_err(dev, "failed to set DMA coherent mask: %d\n", err);
		goto free_irq;
	}

	msi->virt = dma_alloc_attrs(dev, PAGE_SIZE, &msi->phys, GFP_KERNEL,
				    DMA_ATTR_NO_KERNEL_MAPPING);
	if (!msi->virt) {
		dev_err(dev, "failed to allocate DMA memory for MSI\n");
		err = -ENOMEM;
		goto free_irq;
	}

	host->msi = &msi->chip;

	return 0;

free_irq:
	free_irq(msi->irq, pcie);
free_irq_domain:
	irq_domain_remove(msi->domain);
	return err;
}