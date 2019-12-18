#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qcom_iommu_domain {TYPE_1__* iommu; int /*<<< orphan*/  pgtbl_ops; } ;
struct iommu_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (TYPE_1__*) ; 
 int /*<<< orphan*/  free_io_pgtable_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_put_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  kfree (struct qcom_iommu_domain*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct qcom_iommu_domain* to_qcom_iommu_domain (struct iommu_domain*) ; 

__attribute__((used)) static void qcom_iommu_domain_free(struct iommu_domain *domain)
{
	struct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);

	if (WARN_ON(qcom_domain->iommu))    /* forgot to detach? */
		return;

	iommu_put_dma_cookie(domain);

	/* NOTE: unmap can be called after client device is powered off,
	 * for example, with GPUs or anything involving dma-buf.  So we
	 * cannot rely on the device_link.  Make sure the IOMMU is on to
	 * avoid unclocked accesses in the TLB inv path:
	 */
	pm_runtime_get_sync(qcom_domain->iommu->dev);

	free_io_pgtable_ops(qcom_domain->pgtbl_ops);

	pm_runtime_put_sync(qcom_domain->iommu->dev);

	kfree(qcom_domain);
}