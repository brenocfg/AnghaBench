#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {TYPE_2__* io_resource; TYPE_1__* mem_resource; int /*<<< orphan*/ * pci_ops; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  flags; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; struct resource* parent; } ;
struct ar2315_pci_ctrl {int irq; TYPE_3__ pci_ctrl; TYPE_2__ io_res; TYPE_1__ mem_res; int /*<<< orphan*/  domain; int /*<<< orphan*/  cfg_mem; int /*<<< orphan*/  mmr_mem; } ;

/* Variables and functions */
 int AR2315_PCICACHE_DIS ; 
 int /*<<< orphan*/  AR2315_PCIMISC_RST_MODE ; 
 int AR2315_PCIRST_HIGH ; 
 int AR2315_PCIRST_LOW ; 
 int /*<<< orphan*/  AR2315_PCI_CFG_SIZE ; 
 int /*<<< orphan*/  AR2315_PCI_IRQ_COUNT ; 
 int /*<<< orphan*/  AR2315_PCI_MISC_CONFIG ; 
 int /*<<< orphan*/  AR2315_PCI_UNCACHE_CFG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int ar2315_pci_host_setup (struct ar2315_pci_ctrl*) ; 
 int /*<<< orphan*/  ar2315_pci_irq_domain_ops ; 
 int /*<<< orphan*/  ar2315_pci_irq_init (struct ar2315_pci_ctrl*) ; 
 int /*<<< orphan*/  ar2315_pci_ops ; 
 int /*<<< orphan*/  ar2315_pci_reg_mask (struct ar2315_pci_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar2315_pci_reg_read (struct ar2315_pci_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar2315_pci_reg_write (struct ar2315_pci_ctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ar2315_pci_ctrl* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ar2315_pci_ctrl*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  register_pci_controller (TYPE_3__*) ; 

__attribute__((used)) static int ar2315_pci_probe(struct platform_device *pdev)
{
	struct ar2315_pci_ctrl *apc;
	struct device *dev = &pdev->dev;
	struct resource *res;
	int irq, err;

	apc = devm_kzalloc(dev, sizeof(*apc), GFP_KERNEL);
	if (!apc)
		return -ENOMEM;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -EINVAL;
	apc->irq = irq;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "ar2315-pci-ctrl");
	apc->mmr_mem = devm_ioremap_resource(dev, res);
	if (IS_ERR(apc->mmr_mem))
		return PTR_ERR(apc->mmr_mem);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "ar2315-pci-ext");
	if (!res)
		return -EINVAL;

	apc->mem_res.name = "AR2315 PCI mem space";
	apc->mem_res.parent = res;
	apc->mem_res.start = res->start;
	apc->mem_res.end = res->end;
	apc->mem_res.flags = IORESOURCE_MEM;

	/* Remap PCI config space */
	apc->cfg_mem = devm_ioremap_nocache(dev, res->start,
					    AR2315_PCI_CFG_SIZE);
	if (!apc->cfg_mem) {
		dev_err(dev, "failed to remap PCI config space\n");
		return -ENOMEM;
	}

	/* Reset the PCI bus by setting bits 5-4 in PCI_MCFG */
	ar2315_pci_reg_mask(apc, AR2315_PCI_MISC_CONFIG,
			    AR2315_PCIMISC_RST_MODE,
			    AR2315_PCIRST_LOW);
	msleep(100);

	/* Bring the PCI out of reset */
	ar2315_pci_reg_mask(apc, AR2315_PCI_MISC_CONFIG,
			    AR2315_PCIMISC_RST_MODE,
			    AR2315_PCIRST_HIGH | AR2315_PCICACHE_DIS | 0x8);

	ar2315_pci_reg_write(apc, AR2315_PCI_UNCACHE_CFG,
			     0x1E | /* 1GB uncached */
			     (1 << 5) | /* Enable uncached */
			     (0x2 << 30) /* Base: 0x80000000 */);
	ar2315_pci_reg_read(apc, AR2315_PCI_UNCACHE_CFG);

	msleep(500);

	err = ar2315_pci_host_setup(apc);
	if (err)
		return err;

	apc->domain = irq_domain_add_linear(NULL, AR2315_PCI_IRQ_COUNT,
					    &ar2315_pci_irq_domain_ops, apc);
	if (!apc->domain) {
		dev_err(dev, "failed to add IRQ domain\n");
		return -ENOMEM;
	}

	ar2315_pci_irq_init(apc);

	/* PCI controller does not support I/O ports */
	apc->io_res.name = "AR2315 IO space";
	apc->io_res.start = 0;
	apc->io_res.end = 0;
	apc->io_res.flags = IORESOURCE_IO,

	apc->pci_ctrl.pci_ops = &ar2315_pci_ops;
	apc->pci_ctrl.mem_resource = &apc->mem_res,
	apc->pci_ctrl.io_resource = &apc->io_res,

	register_pci_controller(&apc->pci_ctrl);

	dev_info(dev, "register PCI controller\n");

	return 0;
}