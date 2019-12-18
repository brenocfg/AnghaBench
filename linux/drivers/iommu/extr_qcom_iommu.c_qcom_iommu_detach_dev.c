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
struct qcom_iommu_domain {int /*<<< orphan*/ * iommu; } ;
struct qcom_iommu_dev {int /*<<< orphan*/  dev; } ;
struct qcom_iommu_ctx {int /*<<< orphan*/ * domain; } ;
struct iommu_fwspec {unsigned int num_ids; int /*<<< orphan*/ * ids; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_CB_SCTLR ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  iommu_writel (struct qcom_iommu_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct qcom_iommu_ctx* to_ctx (struct iommu_fwspec*,int /*<<< orphan*/ ) ; 
 struct qcom_iommu_dev* to_iommu (struct iommu_fwspec*) ; 
 struct qcom_iommu_domain* to_qcom_iommu_domain (struct iommu_domain*) ; 

__attribute__((used)) static void qcom_iommu_detach_dev(struct iommu_domain *domain, struct device *dev)
{
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	struct qcom_iommu_dev *qcom_iommu = to_iommu(fwspec);
	struct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);
	unsigned i;

	if (!qcom_domain->iommu)
		return;

	pm_runtime_get_sync(qcom_iommu->dev);
	for (i = 0; i < fwspec->num_ids; i++) {
		struct qcom_iommu_ctx *ctx = to_ctx(fwspec, fwspec->ids[i]);

		/* Disable the context bank: */
		iommu_writel(ctx, ARM_SMMU_CB_SCTLR, 0);

		ctx->domain = NULL;
	}
	pm_runtime_put_sync(qcom_iommu->dev);

	qcom_domain->iommu = NULL;
}