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
struct tegra_smmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMMU_TLB_FLUSH ; 
 int SMMU_TLB_FLUSH_ASID (unsigned long) ; 
 int SMMU_TLB_FLUSH_ASID_MATCH ; 
 int SMMU_TLB_FLUSH_VA_GROUP (unsigned long) ; 
 int /*<<< orphan*/  smmu_writel (struct tegra_smmu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void smmu_flush_tlb_group(struct tegra_smmu *smmu,
					unsigned long asid,
					unsigned long iova)
{
	u32 value;

	value = SMMU_TLB_FLUSH_ASID_MATCH | SMMU_TLB_FLUSH_ASID(asid) |
		SMMU_TLB_FLUSH_VA_GROUP(iova);
	smmu_writel(smmu, value, SMMU_TLB_FLUSH);
}