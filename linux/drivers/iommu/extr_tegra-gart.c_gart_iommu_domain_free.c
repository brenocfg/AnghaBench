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
struct iommu_domain {int dummy; } ;
struct TYPE_2__ {struct iommu_domain* active_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* gart_handle ; 
 int /*<<< orphan*/  kfree (struct iommu_domain*) ; 

__attribute__((used)) static void gart_iommu_domain_free(struct iommu_domain *domain)
{
	WARN_ON(gart_handle->active_domain == domain);
	kfree(domain);
}