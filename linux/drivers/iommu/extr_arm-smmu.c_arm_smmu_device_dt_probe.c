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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct arm_smmu_match_data {int /*<<< orphan*/  model; int /*<<< orphan*/  version; } ;
struct arm_smmu_device {int /*<<< orphan*/  features; int /*<<< orphan*/  model; int /*<<< orphan*/  version; int /*<<< orphan*/  num_global_irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_FEAT_COHERENT_WALK ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct arm_smmu_match_data* of_device_get_match_data (struct device*) ; 
 scalar_t__ of_dma_is_coherent (int /*<<< orphan*/ ) ; 
 int of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int using_generic_binding ; 
 int using_legacy_binding ; 

__attribute__((used)) static int arm_smmu_device_dt_probe(struct platform_device *pdev,
				    struct arm_smmu_device *smmu)
{
	const struct arm_smmu_match_data *data;
	struct device *dev = &pdev->dev;
	bool legacy_binding;

	if (of_property_read_u32(dev->of_node, "#global-interrupts",
				 &smmu->num_global_irqs)) {
		dev_err(dev, "missing #global-interrupts property\n");
		return -ENODEV;
	}

	data = of_device_get_match_data(dev);
	smmu->version = data->version;
	smmu->model = data->model;

	legacy_binding = of_find_property(dev->of_node, "mmu-masters", NULL);
	if (legacy_binding && !using_generic_binding) {
		if (!using_legacy_binding)
			pr_notice("deprecated \"mmu-masters\" DT property in use; DMA API support unavailable\n");
		using_legacy_binding = true;
	} else if (!legacy_binding && !using_legacy_binding) {
		using_generic_binding = true;
	} else {
		dev_err(dev, "not probing due to mismatched DT properties\n");
		return -ENODEV;
	}

	if (of_dma_is_coherent(dev->of_node))
		smmu->features |= ARM_SMMU_FEAT_COHERENT_WALK;

	return 0;
}