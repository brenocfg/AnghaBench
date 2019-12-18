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
struct TYPE_4__ {int /*<<< orphan*/  q; } ;
struct TYPE_6__ {int /*<<< orphan*/  q; } ;
struct TYPE_5__ {int /*<<< orphan*/  q; } ;
struct arm_smmu_device {int features; TYPE_1__ priq; TYPE_3__ evtq; TYPE_2__ cmdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_CMDQ_CONS ; 
 int /*<<< orphan*/  ARM_SMMU_CMDQ_PROD ; 
 int /*<<< orphan*/  ARM_SMMU_EVTQ_CONS ; 
 int /*<<< orphan*/  ARM_SMMU_EVTQ_PROD ; 
 int ARM_SMMU_FEAT_PRI ; 
 int /*<<< orphan*/  ARM_SMMU_PRIQ_CONS ; 
 int /*<<< orphan*/  ARM_SMMU_PRIQ_PROD ; 
 int /*<<< orphan*/  CMDQ_ENT_DWORDS ; 
 int /*<<< orphan*/  EVTQ_ENT_DWORDS ; 
 int /*<<< orphan*/  PRIQ_ENT_DWORDS ; 
 int arm_smmu_cmdq_init (struct arm_smmu_device*) ; 
 int arm_smmu_init_one_queue (struct arm_smmu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int arm_smmu_init_queues(struct arm_smmu_device *smmu)
{
	int ret;

	/* cmdq */
	ret = arm_smmu_init_one_queue(smmu, &smmu->cmdq.q, ARM_SMMU_CMDQ_PROD,
				      ARM_SMMU_CMDQ_CONS, CMDQ_ENT_DWORDS,
				      "cmdq");
	if (ret)
		return ret;

	ret = arm_smmu_cmdq_init(smmu);
	if (ret)
		return ret;

	/* evtq */
	ret = arm_smmu_init_one_queue(smmu, &smmu->evtq.q, ARM_SMMU_EVTQ_PROD,
				      ARM_SMMU_EVTQ_CONS, EVTQ_ENT_DWORDS,
				      "evtq");
	if (ret)
		return ret;

	/* priq */
	if (!(smmu->features & ARM_SMMU_FEAT_PRI))
		return 0;

	return arm_smmu_init_one_queue(smmu, &smmu->priq.q, ARM_SMMU_PRIQ_PROD,
				       ARM_SMMU_PRIQ_CONS, PRIQ_ENT_DWORDS,
				       "priq");
}