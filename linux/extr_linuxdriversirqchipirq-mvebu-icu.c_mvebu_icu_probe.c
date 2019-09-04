#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {scalar_t__ start; } ;
struct TYPE_9__ {int /*<<< orphan*/  msi_domain; struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_eoi; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  name; } ;
struct mvebu_icu {int /*<<< orphan*/  domain; scalar_t__ base; TYPE_1__ irq_chip; TYPE_2__* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_BUS_PLATFORM_MSI ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICU_GROUP_SHIFT ; 
 int ICU_GRP_NSR ; 
 scalar_t__ ICU_INT_CFG (int) ; 
 int ICU_MAX_IRQS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 scalar_t__ devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  devm_kasprintf (TYPE_2__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct mvebu_icu* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_chip_eoi_parent ; 
 int /*<<< orphan*/  irq_chip_mask_parent ; 
 int /*<<< orphan*/  irq_chip_set_type_parent ; 
 int /*<<< orphan*/  irq_chip_unmask_parent ; 
 struct device_node* irq_domain_get_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_icu_domain_ops ; 
 int /*<<< orphan*/  mvebu_icu_write_msg ; 
 int /*<<< orphan*/  of_msi_get_domain (TYPE_2__*,struct device_node*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_msi_create_device_domain (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mvebu_icu*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int mvebu_icu_probe(struct platform_device *pdev)
{
	struct mvebu_icu *icu;
	struct device_node *node = pdev->dev.of_node;
	struct device_node *gicp_dn;
	struct resource *res;
	int i;

	icu = devm_kzalloc(&pdev->dev, sizeof(struct mvebu_icu),
			   GFP_KERNEL);
	if (!icu)
		return -ENOMEM;

	icu->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	icu->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(icu->base)) {
		dev_err(&pdev->dev, "Failed to map icu base address.\n");
		return PTR_ERR(icu->base);
	}

	icu->irq_chip.name = devm_kasprintf(&pdev->dev, GFP_KERNEL,
					    "ICU.%x",
					    (unsigned int)res->start);
	if (!icu->irq_chip.name)
		return -ENOMEM;

	icu->irq_chip.irq_mask = irq_chip_mask_parent;
	icu->irq_chip.irq_unmask = irq_chip_unmask_parent;
	icu->irq_chip.irq_eoi = irq_chip_eoi_parent;
	icu->irq_chip.irq_set_type = irq_chip_set_type_parent;
#ifdef CONFIG_SMP
	icu->irq_chip.irq_set_affinity = irq_chip_set_affinity_parent;
#endif

	/*
	 * We're probed after MSI domains have been resolved, so force
	 * resolution here.
	 */
	pdev->dev.msi_domain = of_msi_get_domain(&pdev->dev, node,
						 DOMAIN_BUS_PLATFORM_MSI);
	if (!pdev->dev.msi_domain)
		return -EPROBE_DEFER;

	gicp_dn = irq_domain_get_of_node(pdev->dev.msi_domain);
	if (!gicp_dn)
		return -ENODEV;

	/*
	 * Clean all ICU interrupts with type SPI_NSR, required to
	 * avoid unpredictable SPI assignments done by firmware.
	 */
	for (i = 0 ; i < ICU_MAX_IRQS ; i++) {
		u32 icu_int = readl_relaxed(icu->base + ICU_INT_CFG(i));
		if ((icu_int >> ICU_GROUP_SHIFT) == ICU_GRP_NSR)
			writel_relaxed(0x0, icu->base + ICU_INT_CFG(i));
	}

	icu->domain =
		platform_msi_create_device_domain(&pdev->dev, ICU_MAX_IRQS,
						  mvebu_icu_write_msg,
						  &mvebu_icu_domain_ops, icu);
	if (!icu->domain) {
		dev_err(&pdev->dev, "Failed to create ICU domain\n");
		return -ENOMEM;
	}

	return 0;
}