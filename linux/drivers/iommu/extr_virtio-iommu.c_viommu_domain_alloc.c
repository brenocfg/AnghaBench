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
struct viommu_domain {struct iommu_domain domain; int /*<<< orphan*/  mappings; int /*<<< orphan*/  mappings_lock; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IOMMU_DOMAIN_DMA ; 
 unsigned int IOMMU_DOMAIN_UNMANAGED ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 scalar_t__ iommu_get_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  kfree (struct viommu_domain*) ; 
 struct viommu_domain* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iommu_domain *viommu_domain_alloc(unsigned type)
{
	struct viommu_domain *vdomain;

	if (type != IOMMU_DOMAIN_UNMANAGED && type != IOMMU_DOMAIN_DMA)
		return NULL;

	vdomain = kzalloc(sizeof(*vdomain), GFP_KERNEL);
	if (!vdomain)
		return NULL;

	mutex_init(&vdomain->mutex);
	spin_lock_init(&vdomain->mappings_lock);
	vdomain->mappings = RB_ROOT_CACHED;

	if (type == IOMMU_DOMAIN_DMA &&
	    iommu_get_dma_cookie(&vdomain->domain)) {
		kfree(vdomain);
		return NULL;
	}

	return &vdomain->domain;
}