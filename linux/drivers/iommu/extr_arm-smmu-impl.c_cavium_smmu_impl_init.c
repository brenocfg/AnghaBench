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
struct arm_smmu_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * impl; } ;
struct cavium_smmu {struct arm_smmu_device smmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct arm_smmu_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cavium_impl ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct arm_smmu_device*) ; 
 struct cavium_smmu* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct arm_smmu_device *cavium_smmu_impl_init(struct arm_smmu_device *smmu)
{
	struct cavium_smmu *cs;

	cs = devm_kzalloc(smmu->dev, sizeof(*cs), GFP_KERNEL);
	if (!cs)
		return ERR_PTR(-ENOMEM);

	cs->smmu = *smmu;
	cs->smmu.impl = &cavium_impl;

	devm_kfree(smmu->dev, smmu);

	return &cs->smmu;
}