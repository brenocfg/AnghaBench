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
struct qcom_iommu_dev {struct qcom_iommu_ctx** ctxs; } ;
struct qcom_iommu_ctx {int dummy; } ;
struct iommu_fwspec {int dummy; } ;

/* Variables and functions */
 struct qcom_iommu_dev* to_iommu (struct iommu_fwspec*) ; 

__attribute__((used)) static struct qcom_iommu_ctx * to_ctx(struct iommu_fwspec *fwspec, unsigned asid)
{
	struct qcom_iommu_dev *qcom_iommu = to_iommu(fwspec);
	if (!qcom_iommu)
		return NULL;
	return qcom_iommu->ctxs[asid - 1];
}