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
struct device {TYPE_2__* iommu_fwspec; } ;
struct TYPE_3__ {int assigned; } ;
struct arm_smmu_master_data {TYPE_1__ ste; } ;
struct TYPE_4__ {struct arm_smmu_master_data* iommu_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_install_ste_for_dev (TYPE_2__*) ; 

__attribute__((used)) static void arm_smmu_detach_dev(struct device *dev)
{
	struct arm_smmu_master_data *master = dev->iommu_fwspec->iommu_priv;

	master->ste.assigned = false;
	arm_smmu_install_ste_for_dev(dev->iommu_fwspec);
}