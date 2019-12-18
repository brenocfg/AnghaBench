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
struct smmu_pmu {int irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 unsigned long IRQF_NOBALANCING ; 
 unsigned long IRQF_NO_THREAD ; 
 unsigned long IRQF_SHARED ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long,char*,struct smmu_pmu*) ; 
 int /*<<< orphan*/  smmu_pmu_handle_irq ; 
 int /*<<< orphan*/  smmu_pmu_setup_msi (struct smmu_pmu*) ; 

__attribute__((used)) static int smmu_pmu_setup_irq(struct smmu_pmu *pmu)
{
	unsigned long flags = IRQF_NOBALANCING | IRQF_SHARED | IRQF_NO_THREAD;
	int irq, ret = -ENXIO;

	smmu_pmu_setup_msi(pmu);

	irq = pmu->irq;
	if (irq)
		ret = devm_request_irq(pmu->dev, irq, smmu_pmu_handle_irq,
				       flags, "smmuv3-pmu", pmu);
	return ret;
}