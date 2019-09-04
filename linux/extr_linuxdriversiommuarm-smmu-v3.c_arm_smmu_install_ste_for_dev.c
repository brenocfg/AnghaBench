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
typedef  scalar_t__ u32 ;
struct iommu_fwspec {int num_ids; scalar_t__* ids; struct arm_smmu_master_data* iommu_priv; } ;
struct arm_smmu_master_data {int /*<<< orphan*/  ste; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/ * arm_smmu_get_step_for_sid (struct arm_smmu_device*,scalar_t__) ; 
 int /*<<< orphan*/  arm_smmu_write_strtab_ent (struct arm_smmu_device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arm_smmu_install_ste_for_dev(struct iommu_fwspec *fwspec)
{
	int i, j;
	struct arm_smmu_master_data *master = fwspec->iommu_priv;
	struct arm_smmu_device *smmu = master->smmu;

	for (i = 0; i < fwspec->num_ids; ++i) {
		u32 sid = fwspec->ids[i];
		__le64 *step = arm_smmu_get_step_for_sid(smmu, sid);

		/* Bridged PCI devices may end up with duplicated IDs */
		for (j = 0; j < i; j++)
			if (fwspec->ids[j] == sid)
				break;
		if (j < i)
			continue;

		arm_smmu_write_strtab_ent(smmu, sid, step, &master->ste);
	}
}