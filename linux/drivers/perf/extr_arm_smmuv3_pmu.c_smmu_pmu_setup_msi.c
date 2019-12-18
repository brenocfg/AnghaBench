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
struct smmu_pmu {int /*<<< orphan*/  irq; scalar_t__ reg_base; struct device* dev; } ;
struct msi_desc {int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SMMU_PMCG_CFGR ; 
 int SMMU_PMCG_CFGR_MSI ; 
 scalar_t__ SMMU_PMCG_IRQ_CFG0 ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  devm_add_action (struct device*,int /*<<< orphan*/ ,struct device*) ; 
 struct msi_desc* first_msi_entry (struct device*) ; 
 int platform_msi_domain_alloc_irqs (struct device*,int,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  smmu_pmu_free_msis ; 
 int /*<<< orphan*/  smmu_pmu_write_msi_msg ; 
 int /*<<< orphan*/  writeq_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void smmu_pmu_setup_msi(struct smmu_pmu *pmu)
{
	struct msi_desc *desc;
	struct device *dev = pmu->dev;
	int ret;

	/* Clear MSI address reg */
	writeq_relaxed(0, pmu->reg_base + SMMU_PMCG_IRQ_CFG0);

	/* MSI supported or not */
	if (!(readl(pmu->reg_base + SMMU_PMCG_CFGR) & SMMU_PMCG_CFGR_MSI))
		return;

	ret = platform_msi_domain_alloc_irqs(dev, 1, smmu_pmu_write_msi_msg);
	if (ret) {
		dev_warn(dev, "failed to allocate MSIs\n");
		return;
	}

	desc = first_msi_entry(dev);
	if (desc)
		pmu->irq = desc->irq;

	/* Add callback to free MSIs on teardown */
	devm_add_action(dev, smmu_pmu_free_msis, dev);
}