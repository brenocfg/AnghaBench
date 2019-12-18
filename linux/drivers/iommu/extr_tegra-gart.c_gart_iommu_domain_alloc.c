#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int force_aperture; scalar_t__ aperture_end; int /*<<< orphan*/  aperture_start; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct TYPE_4__ {scalar_t__ iovmm_end; int /*<<< orphan*/  iovmm_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IOMMU_DOMAIN_UNMANAGED ; 
 TYPE_2__* gart_handle ; 
 struct iommu_domain* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iommu_domain *gart_iommu_domain_alloc(unsigned type)
{
	struct iommu_domain *domain;

	if (type != IOMMU_DOMAIN_UNMANAGED)
		return NULL;

	domain = kzalloc(sizeof(*domain), GFP_KERNEL);
	if (domain) {
		domain->geometry.aperture_start = gart_handle->iovmm_base;
		domain->geometry.aperture_end = gart_handle->iovmm_end - 1;
		domain->geometry.force_aperture = true;
	}

	return domain;
}