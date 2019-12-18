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
struct resource {int /*<<< orphan*/  start; } ;
struct device {scalar_t__ pm_domain; int /*<<< orphan*/  fwnode; scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct arm_smmu_device {int num_global_irqs; int* irqs; int num_clks; scalar_t__ version; int /*<<< orphan*/  iommu; struct device* dev; int /*<<< orphan*/  num_context_banks; int /*<<< orphan*/  num_context_irqs; int /*<<< orphan*/  clks; int /*<<< orphan*/  numpage; struct arm_smmu_device* base; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 scalar_t__ ARM_SMMU_V2 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct arm_smmu_device*) ; 
 int PTR_ERR (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  arm_smmu_bus_init () ; 
 int arm_smmu_device_acpi_probe (struct platform_device*,struct arm_smmu_device*) ; 
 int arm_smmu_device_cfg_probe (struct arm_smmu_device*) ; 
 int arm_smmu_device_dt_probe (struct platform_device*,struct arm_smmu_device*) ; 
 int /*<<< orphan*/  arm_smmu_device_reset (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  arm_smmu_global_fault ; 
 struct arm_smmu_device* arm_smmu_impl_init (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  arm_smmu_ops ; 
 int /*<<< orphan*/  arm_smmu_test_smr_masks (struct arm_smmu_device*) ; 
 int clk_bulk_prepare_enable (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_clk_bulk_get_all (struct device*,int /*<<< orphan*/ *) ; 
 struct arm_smmu_device* devm_ioremap_resource (struct device*,struct resource*) ; 
 int* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct arm_smmu_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct arm_smmu_device*) ; 
 int iommu_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_fwnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iommu_device_sysfs_add (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct arm_smmu_device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  using_legacy_binding ; 

__attribute__((used)) static int arm_smmu_device_probe(struct platform_device *pdev)
{
	struct resource *res;
	resource_size_t ioaddr;
	struct arm_smmu_device *smmu;
	struct device *dev = &pdev->dev;
	int num_irqs, i, err;

	smmu = devm_kzalloc(dev, sizeof(*smmu), GFP_KERNEL);
	if (!smmu) {
		dev_err(dev, "failed to allocate arm_smmu_device\n");
		return -ENOMEM;
	}
	smmu->dev = dev;

	if (dev->of_node)
		err = arm_smmu_device_dt_probe(pdev, smmu);
	else
		err = arm_smmu_device_acpi_probe(pdev, smmu);

	if (err)
		return err;

	smmu = arm_smmu_impl_init(smmu);
	if (IS_ERR(smmu))
		return PTR_ERR(smmu);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ioaddr = res->start;
	smmu->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(smmu->base))
		return PTR_ERR(smmu->base);
	/*
	 * The resource size should effectively match the value of SMMU_TOP;
	 * stash that temporarily until we know PAGESIZE to validate it with.
	 */
	smmu->numpage = resource_size(res);

	num_irqs = 0;
	while ((res = platform_get_resource(pdev, IORESOURCE_IRQ, num_irqs))) {
		num_irqs++;
		if (num_irqs > smmu->num_global_irqs)
			smmu->num_context_irqs++;
	}

	if (!smmu->num_context_irqs) {
		dev_err(dev, "found %d interrupts but expected at least %d\n",
			num_irqs, smmu->num_global_irqs + 1);
		return -ENODEV;
	}

	smmu->irqs = devm_kcalloc(dev, num_irqs, sizeof(*smmu->irqs),
				  GFP_KERNEL);
	if (!smmu->irqs) {
		dev_err(dev, "failed to allocate %d irqs\n", num_irqs);
		return -ENOMEM;
	}

	for (i = 0; i < num_irqs; ++i) {
		int irq = platform_get_irq(pdev, i);

		if (irq < 0) {
			dev_err(dev, "failed to get irq index %d\n", i);
			return -ENODEV;
		}
		smmu->irqs[i] = irq;
	}

	err = devm_clk_bulk_get_all(dev, &smmu->clks);
	if (err < 0) {
		dev_err(dev, "failed to get clocks %d\n", err);
		return err;
	}
	smmu->num_clks = err;

	err = clk_bulk_prepare_enable(smmu->num_clks, smmu->clks);
	if (err)
		return err;

	err = arm_smmu_device_cfg_probe(smmu);
	if (err)
		return err;

	if (smmu->version == ARM_SMMU_V2) {
		if (smmu->num_context_banks > smmu->num_context_irqs) {
			dev_err(dev,
			      "found only %d context irq(s) but %d required\n",
			      smmu->num_context_irqs, smmu->num_context_banks);
			return -ENODEV;
		}

		/* Ignore superfluous interrupts */
		smmu->num_context_irqs = smmu->num_context_banks;
	}

	for (i = 0; i < smmu->num_global_irqs; ++i) {
		err = devm_request_irq(smmu->dev, smmu->irqs[i],
				       arm_smmu_global_fault,
				       IRQF_SHARED,
				       "arm-smmu global fault",
				       smmu);
		if (err) {
			dev_err(dev, "failed to request global IRQ %d (%u)\n",
				i, smmu->irqs[i]);
			return err;
		}
	}

	err = iommu_device_sysfs_add(&smmu->iommu, smmu->dev, NULL,
				     "smmu.%pa", &ioaddr);
	if (err) {
		dev_err(dev, "Failed to register iommu in sysfs\n");
		return err;
	}

	iommu_device_set_ops(&smmu->iommu, &arm_smmu_ops);
	iommu_device_set_fwnode(&smmu->iommu, dev->fwnode);

	err = iommu_device_register(&smmu->iommu);
	if (err) {
		dev_err(dev, "Failed to register iommu\n");
		return err;
	}

	platform_set_drvdata(pdev, smmu);
	arm_smmu_device_reset(smmu);
	arm_smmu_test_smr_masks(smmu);

	/*
	 * We want to avoid touching dev->power.lock in fastpaths unless
	 * it's really going to do something useful - pm_runtime_enabled()
	 * can serve as an ideal proxy for that decision. So, conditionally
	 * enable pm_runtime.
	 */
	if (dev->pm_domain) {
		pm_runtime_set_active(dev);
		pm_runtime_enable(dev);
	}

	/*
	 * For ACPI and generic DT bindings, an SMMU will be probed before
	 * any device which might need it, so we want the bus ops in place
	 * ready to handle default domain setup as soon as any SMMU exists.
	 */
	if (!using_legacy_binding)
		arm_smmu_bus_init();

	return 0;
}