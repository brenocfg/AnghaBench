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
struct iommu_domain {int dummy; } ;
struct mtk_iommu_domain {struct iommu_domain domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IOMMU_DOMAIN_UNMANAGED ; 
 struct mtk_iommu_domain* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iommu_domain *mtk_iommu_domain_alloc(unsigned type)
{
	struct mtk_iommu_domain *dom;

	if (type != IOMMU_DOMAIN_UNMANAGED)
		return NULL;

	dom = kzalloc(sizeof(*dom), GFP_KERNEL);
	if (!dom)
		return NULL;

	return &dom->domain;
}