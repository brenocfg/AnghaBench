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
typedef  int /*<<< orphan*/  u32 ;
struct iommu_domain {TYPE_1__* ops; } ;
struct TYPE_2__ {void (* domain_window_disable ) (struct iommu_domain*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void stub1 (struct iommu_domain*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void iommu_domain_window_disable(struct iommu_domain *domain, u32 wnd_nr)
{
	if (unlikely(domain->ops->domain_window_disable == NULL))
		return;

	return domain->ops->domain_window_disable(domain, wnd_nr);
}