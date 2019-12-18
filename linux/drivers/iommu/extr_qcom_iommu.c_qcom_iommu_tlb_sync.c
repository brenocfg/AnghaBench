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
struct qcom_iommu_ctx {int /*<<< orphan*/  dev; scalar_t__ base; } ;
struct iommu_fwspec {unsigned int num_ids; int /*<<< orphan*/ * ids; } ;

/* Variables and functions */
 scalar_t__ ARM_SMMU_CB_TLBSTATUS ; 
 int /*<<< orphan*/  ARM_SMMU_CB_TLBSYNC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iommu_writel (struct qcom_iommu_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readl_poll_timeout (scalar_t__,unsigned int,int,int /*<<< orphan*/ ,int) ; 
 struct qcom_iommu_ctx* to_ctx (struct iommu_fwspec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_iommu_tlb_sync(void *cookie)
{
	struct iommu_fwspec *fwspec = cookie;
	unsigned i;

	for (i = 0; i < fwspec->num_ids; i++) {
		struct qcom_iommu_ctx *ctx = to_ctx(fwspec, fwspec->ids[i]);
		unsigned int val, ret;

		iommu_writel(ctx, ARM_SMMU_CB_TLBSYNC, 0);

		ret = readl_poll_timeout(ctx->base + ARM_SMMU_CB_TLBSTATUS, val,
					 (val & 0x1) == 0, 0, 5000000);
		if (ret)
			dev_err(ctx->dev, "timeout waiting for TLB SYNC\n");
	}
}