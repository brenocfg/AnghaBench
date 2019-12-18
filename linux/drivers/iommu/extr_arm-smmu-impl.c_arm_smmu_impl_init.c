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
struct arm_smmu_device {int model; int /*<<< orphan*/ * impl; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
#define  ARM_MMU500 129 
#define  CAVIUM_SMMUV2 128 
 int /*<<< orphan*/  arm_mmu500_impl ; 
 int /*<<< orphan*/  calxeda_impl ; 
 struct arm_smmu_device* cavium_smmu_impl_init (struct arm_smmu_device*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 

struct arm_smmu_device *arm_smmu_impl_init(struct arm_smmu_device *smmu)
{
	/*
	 * We will inevitably have to combine model-specific implementation
	 * quirks with platform-specific integration quirks, but everything
	 * we currently support happens to work out as straightforward
	 * mutually-exclusive assignments.
	 */
	switch (smmu->model) {
	case ARM_MMU500:
		smmu->impl = &arm_mmu500_impl;
		break;
	case CAVIUM_SMMUV2:
		return cavium_smmu_impl_init(smmu);
	default:
		break;
	}

	if (of_property_read_bool(smmu->dev->of_node,
				  "calxeda,smmu-secure-config-access"))
		smmu->impl = &calxeda_impl;

	return smmu;
}