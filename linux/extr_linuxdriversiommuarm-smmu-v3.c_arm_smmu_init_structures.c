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
struct arm_smmu_device {int /*<<< orphan*/  sync_nr; } ;

/* Variables and functions */
 int arm_smmu_init_queues (struct arm_smmu_device*) ; 
 int arm_smmu_init_strtab (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arm_smmu_init_structures(struct arm_smmu_device *smmu)
{
	int ret;

	atomic_set(&smmu->sync_nr, 0);
	ret = arm_smmu_init_queues(smmu);
	if (ret)
		return ret;

	return arm_smmu_init_strtab(smmu);
}