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
typedef  int u32 ;
struct smmu_pmu {int /*<<< orphan*/  options; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  IORT_SMMU_V3_PMCG_HISI_HIP08 128 
 int /*<<< orphan*/  SMMU_PMCG_EVCNTR_RDONLY ; 
 scalar_t__ dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smmu_pmu_get_acpi_options(struct smmu_pmu *smmu_pmu)
{
	u32 model;

	model = *(u32 *)dev_get_platdata(smmu_pmu->dev);

	switch (model) {
	case IORT_SMMU_V3_PMCG_HISI_HIP08:
		/* HiSilicon Erratum 162001800 */
		smmu_pmu->options |= SMMU_PMCG_EVCNTR_RDONLY;
		break;
	}

	dev_notice(smmu_pmu->dev, "option mask 0x%x\n", smmu_pmu->options);
}