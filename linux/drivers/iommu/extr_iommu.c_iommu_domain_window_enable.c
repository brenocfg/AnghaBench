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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct iommu_domain {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int (* domain_window_enable ) (struct iommu_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct iommu_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int iommu_domain_window_enable(struct iommu_domain *domain, u32 wnd_nr,
			       phys_addr_t paddr, u64 size, int prot)
{
	if (unlikely(domain->ops->domain_window_enable == NULL))
		return -ENODEV;

	return domain->ops->domain_window_enable(domain, wnd_nr, paddr, size,
						 prot);
}