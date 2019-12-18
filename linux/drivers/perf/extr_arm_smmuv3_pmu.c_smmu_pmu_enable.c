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
struct smmu_pmu {scalar_t__ reg_base; } ;
struct pmu {int dummy; } ;

/* Variables and functions */
 scalar_t__ SMMU_PMCG_CR ; 
 int /*<<< orphan*/  SMMU_PMCG_CR_ENABLE ; 
 scalar_t__ SMMU_PMCG_IRQ_CTRL ; 
 int /*<<< orphan*/  SMMU_PMCG_IRQ_CTRL_IRQEN ; 
 struct smmu_pmu* to_smmu_pmu (struct pmu*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void smmu_pmu_enable(struct pmu *pmu)
{
	struct smmu_pmu *smmu_pmu = to_smmu_pmu(pmu);

	writel(SMMU_PMCG_IRQ_CTRL_IRQEN,
	       smmu_pmu->reg_base + SMMU_PMCG_IRQ_CTRL);
	writel(SMMU_PMCG_CR_ENABLE, smmu_pmu->reg_base + SMMU_PMCG_CR);
}