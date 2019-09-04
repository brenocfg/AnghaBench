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
struct iommu_domain {scalar_t__ iova_cookie; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IOMMU_DMA_IOVA_COOKIE ; 
 scalar_t__ cookie_alloc (int /*<<< orphan*/ ) ; 

int iommu_get_dma_cookie(struct iommu_domain *domain)
{
	if (domain->iova_cookie)
		return -EEXIST;

	domain->iova_cookie = cookie_alloc(IOMMU_DMA_IOVA_COOKIE);
	if (!domain->iova_cookie)
		return -ENOMEM;

	return 0;
}