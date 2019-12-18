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
struct TYPE_2__ {int force_aperture; int /*<<< orphan*/  aperture_end; scalar_t__ aperture_start; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct mtk_iommu_domain {struct iommu_domain domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IOMMU_DOMAIN_DMA ; 
 scalar_t__ iommu_get_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  iommu_put_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  kfree (struct mtk_iommu_domain*) ; 
 struct mtk_iommu_domain* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mtk_iommu_domain_finalise (struct mtk_iommu_domain*) ; 

__attribute__((used)) static struct iommu_domain *mtk_iommu_domain_alloc(unsigned type)
{
	struct mtk_iommu_domain *dom;

	if (type != IOMMU_DOMAIN_DMA)
		return NULL;

	dom = kzalloc(sizeof(*dom), GFP_KERNEL);
	if (!dom)
		return NULL;

	if (iommu_get_dma_cookie(&dom->domain))
		goto  free_dom;

	if (mtk_iommu_domain_finalise(dom))
		goto  put_dma_cookie;

	dom->domain.geometry.aperture_start = 0;
	dom->domain.geometry.aperture_end = DMA_BIT_MASK(32);
	dom->domain.geometry.force_aperture = true;

	return &dom->domain;

put_dma_cookie:
	iommu_put_dma_cookie(&dom->domain);
free_dom:
	kfree(dom);
	return NULL;
}