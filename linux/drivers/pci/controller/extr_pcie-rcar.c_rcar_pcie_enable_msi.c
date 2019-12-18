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
struct TYPE_4__ {int /*<<< orphan*/  teardown_irq; int /*<<< orphan*/  setup_irqs; int /*<<< orphan*/  setup_irq; struct device* dev; } ;
struct rcar_msi {scalar_t__ pages; int /*<<< orphan*/  irq2; int /*<<< orphan*/  irq1; int /*<<< orphan*/  domain; TYPE_2__ chip; int /*<<< orphan*/  lock; } ;
struct rcar_pcie {struct rcar_msi msi; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT_PCI_MSI_NR ; 
 int IRQF_NO_THREAD ; 
 int IRQF_SHARED ; 
 int MSIFE ; 
 int /*<<< orphan*/  PCIEMSIALR ; 
 int /*<<< orphan*/  PCIEMSIAUR ; 
 int /*<<< orphan*/  PCIEMSIIER ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct rcar_pcie*) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_domain_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ rcar_msi_irq_chip ; 
 int /*<<< orphan*/  rcar_msi_setup_irq ; 
 int /*<<< orphan*/  rcar_msi_setup_irqs ; 
 int /*<<< orphan*/  rcar_msi_teardown_irq ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pcie_msi_irq ; 
 int /*<<< orphan*/  rcar_pcie_unmap_msi (struct rcar_pcie*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static int rcar_pcie_enable_msi(struct rcar_pcie *pcie)
{
	struct device *dev = pcie->dev;
	struct rcar_msi *msi = &pcie->msi;
	phys_addr_t base;
	int err, i;

	mutex_init(&msi->lock);

	msi->chip.dev = dev;
	msi->chip.setup_irq = rcar_msi_setup_irq;
	msi->chip.setup_irqs = rcar_msi_setup_irqs;
	msi->chip.teardown_irq = rcar_msi_teardown_irq;

	msi->domain = irq_domain_add_linear(dev->of_node, INT_PCI_MSI_NR,
					    &msi_domain_ops, &msi->chip);
	if (!msi->domain) {
		dev_err(dev, "failed to create IRQ domain\n");
		return -ENOMEM;
	}

	for (i = 0; i < INT_PCI_MSI_NR; i++)
		irq_create_mapping(msi->domain, i);

	/* Two irqs are for MSI, but they are also used for non-MSI irqs */
	err = devm_request_irq(dev, msi->irq1, rcar_pcie_msi_irq,
			       IRQF_SHARED | IRQF_NO_THREAD,
			       rcar_msi_irq_chip.name, pcie);
	if (err < 0) {
		dev_err(dev, "failed to request IRQ: %d\n", err);
		goto err;
	}

	err = devm_request_irq(dev, msi->irq2, rcar_pcie_msi_irq,
			       IRQF_SHARED | IRQF_NO_THREAD,
			       rcar_msi_irq_chip.name, pcie);
	if (err < 0) {
		dev_err(dev, "failed to request IRQ: %d\n", err);
		goto err;
	}

	/* setup MSI data target */
	msi->pages = __get_free_pages(GFP_KERNEL, 0);
	if (!msi->pages) {
		err = -ENOMEM;
		goto err;
	}
	base = virt_to_phys((void *)msi->pages);

	rcar_pci_write_reg(pcie, lower_32_bits(base) | MSIFE, PCIEMSIALR);
	rcar_pci_write_reg(pcie, upper_32_bits(base), PCIEMSIAUR);

	/* enable all MSI interrupts */
	rcar_pci_write_reg(pcie, 0xffffffff, PCIEMSIIER);

	return 0;

err:
	rcar_pcie_unmap_msi(pcie);
	return err;
}