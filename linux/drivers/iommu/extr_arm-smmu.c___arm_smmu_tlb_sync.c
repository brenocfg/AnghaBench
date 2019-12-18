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
struct arm_smmu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_DUMMY_VAL ; 
 unsigned int TLB_LOOP_TIMEOUT ; 
 unsigned int TLB_SPIN_COUNT ; 
 int arm_smmu_readl (struct arm_smmu_device*,int,int) ; 
 int /*<<< orphan*/  arm_smmu_writel (struct arm_smmu_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int sTLBGSTATUS_GSACTIVE ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

__attribute__((used)) static void __arm_smmu_tlb_sync(struct arm_smmu_device *smmu, int page,
				int sync, int status)
{
	unsigned int spin_cnt, delay;
	u32 reg;

	arm_smmu_writel(smmu, page, sync, QCOM_DUMMY_VAL);
	for (delay = 1; delay < TLB_LOOP_TIMEOUT; delay *= 2) {
		for (spin_cnt = TLB_SPIN_COUNT; spin_cnt > 0; spin_cnt--) {
			reg = arm_smmu_readl(smmu, page, status);
			if (!(reg & sTLBGSTATUS_GSACTIVE))
				return;
			cpu_relax();
		}
		udelay(delay);
	}
	dev_err_ratelimited(smmu->dev,
			    "TLB sync timed out -- SMMU may be deadlocked\n");
}