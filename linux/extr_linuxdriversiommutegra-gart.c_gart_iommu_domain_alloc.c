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
struct TYPE_2__ {int force_aperture; scalar_t__ aperture_end; scalar_t__ aperture_start; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct gart_domain {struct iommu_domain domain; struct gart_device* gart; } ;
struct gart_device {int page_count; scalar_t__ iovmm_base; } ;

/* Variables and functions */
 int GART_PAGE_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IOMMU_DOMAIN_UNMANAGED ; 
 struct gart_device* gart_handle ; 
 struct gart_domain* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iommu_domain *gart_iommu_domain_alloc(unsigned type)
{
	struct gart_domain *gart_domain;
	struct gart_device *gart;

	if (type != IOMMU_DOMAIN_UNMANAGED)
		return NULL;

	gart = gart_handle;
	if (!gart)
		return NULL;

	gart_domain = kzalloc(sizeof(*gart_domain), GFP_KERNEL);
	if (!gart_domain)
		return NULL;

	gart_domain->gart = gart;
	gart_domain->domain.geometry.aperture_start = gart->iovmm_base;
	gart_domain->domain.geometry.aperture_end = gart->iovmm_base +
					gart->page_count * GART_PAGE_SIZE - 1;
	gart_domain->domain.geometry.force_aperture = true;

	return &gart_domain->domain;
}