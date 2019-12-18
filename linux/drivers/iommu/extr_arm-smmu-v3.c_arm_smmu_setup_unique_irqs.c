#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int irq; } ;
struct TYPE_8__ {TYPE_3__ q; } ;
struct TYPE_5__ {int irq; } ;
struct TYPE_6__ {TYPE_1__ q; } ;
struct arm_smmu_device {int gerr_irq; int features; int /*<<< orphan*/  dev; TYPE_4__ priq; TYPE_2__ evtq; } ;

/* Variables and functions */
 int ARM_SMMU_FEAT_PRI ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  arm_smmu_evtq_thread ; 
 int /*<<< orphan*/  arm_smmu_gerror_handler ; 
 int /*<<< orphan*/  arm_smmu_priq_thread ; 
 int /*<<< orphan*/  arm_smmu_setup_msis (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct arm_smmu_device*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct arm_smmu_device*) ; 

__attribute__((used)) static void arm_smmu_setup_unique_irqs(struct arm_smmu_device *smmu)
{
	int irq, ret;

	arm_smmu_setup_msis(smmu);

	/* Request interrupt lines */
	irq = smmu->evtq.q.irq;
	if (irq) {
		ret = devm_request_threaded_irq(smmu->dev, irq, NULL,
						arm_smmu_evtq_thread,
						IRQF_ONESHOT,
						"arm-smmu-v3-evtq", smmu);
		if (ret < 0)
			dev_warn(smmu->dev, "failed to enable evtq irq\n");
	} else {
		dev_warn(smmu->dev, "no evtq irq - events will not be reported!\n");
	}

	irq = smmu->gerr_irq;
	if (irq) {
		ret = devm_request_irq(smmu->dev, irq, arm_smmu_gerror_handler,
				       0, "arm-smmu-v3-gerror", smmu);
		if (ret < 0)
			dev_warn(smmu->dev, "failed to enable gerror irq\n");
	} else {
		dev_warn(smmu->dev, "no gerr irq - errors will not be reported!\n");
	}

	if (smmu->features & ARM_SMMU_FEAT_PRI) {
		irq = smmu->priq.q.irq;
		if (irq) {
			ret = devm_request_threaded_irq(smmu->dev, irq, NULL,
							arm_smmu_priq_thread,
							IRQF_ONESHOT,
							"arm-smmu-v3-priq",
							smmu);
			if (ret < 0)
				dev_warn(smmu->dev,
					 "failed to enable priq irq\n");
		} else {
			dev_warn(smmu->dev, "no priq irq - PRI will be broken\n");
		}
	}
}