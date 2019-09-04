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
struct qcom_iommu_dev {int dummy; } ;
struct iommu_fwspec {struct qcom_iommu_dev* iommu_priv; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  qcom_iommu_ops ; 

__attribute__((used)) static struct qcom_iommu_dev * to_iommu(struct iommu_fwspec *fwspec)
{
	if (!fwspec || fwspec->ops != &qcom_iommu_ops)
		return NULL;
	return fwspec->iommu_priv;
}