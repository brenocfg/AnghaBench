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
struct mtk_iommu_domain {int /*<<< orphan*/  iop; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_io_pgtable_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_put_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  kfree (struct mtk_iommu_domain*) ; 
 struct mtk_iommu_domain* to_mtk_domain (struct iommu_domain*) ; 

__attribute__((used)) static void mtk_iommu_domain_free(struct iommu_domain *domain)
{
	struct mtk_iommu_domain *dom = to_mtk_domain(domain);

	free_io_pgtable_ops(dom->iop);
	iommu_put_dma_cookie(domain);
	kfree(to_mtk_domain(domain));
}