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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct qcom_iommu_ctx {int /*<<< orphan*/  asid; int /*<<< orphan*/  dev; int /*<<< orphan*/  domain; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_CB_FAR ; 
 int /*<<< orphan*/  ARM_SMMU_CB_FSR ; 
 int /*<<< orphan*/  ARM_SMMU_CB_FSYNR0 ; 
 int /*<<< orphan*/  ARM_SMMU_CB_RESUME ; 
 int FSR_FAULT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RESUME_TERMINATE ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int iommu_readl (struct qcom_iommu_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_readq (struct qcom_iommu_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_writel (struct qcom_iommu_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  report_iommu_fault (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t qcom_iommu_fault(int irq, void *dev)
{
	struct qcom_iommu_ctx *ctx = dev;
	u32 fsr, fsynr;
	u64 iova;

	fsr = iommu_readl(ctx, ARM_SMMU_CB_FSR);

	if (!(fsr & FSR_FAULT))
		return IRQ_NONE;

	fsynr = iommu_readl(ctx, ARM_SMMU_CB_FSYNR0);
	iova = iommu_readq(ctx, ARM_SMMU_CB_FAR);

	if (!report_iommu_fault(ctx->domain, ctx->dev, iova, 0)) {
		dev_err_ratelimited(ctx->dev,
				    "Unhandled context fault: fsr=0x%x, "
				    "iova=0x%016llx, fsynr=0x%x, cb=%d\n",
				    fsr, iova, fsynr, ctx->asid);
	}

	iommu_writel(ctx, ARM_SMMU_CB_FSR, fsr);
	iommu_writel(ctx, ARM_SMMU_CB_RESUME, RESUME_TERMINATE);

	return IRQ_HANDLED;
}