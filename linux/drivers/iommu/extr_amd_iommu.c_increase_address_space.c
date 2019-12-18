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
typedef  int /*<<< orphan*/  u64 ;
struct protection_domain {scalar_t__ mode; int /*<<< orphan*/  lock; int /*<<< orphan*/ * pt_root; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ PAGE_MODE_6_LEVEL ; 
 int /*<<< orphan*/  PM_LEVEL_PDE (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long PM_LEVEL_SIZE (scalar_t__) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_virt_to_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool increase_address_space(struct protection_domain *domain,
				   unsigned long address,
				   gfp_t gfp)
{
	unsigned long flags;
	bool ret = false;
	u64 *pte;

	spin_lock_irqsave(&domain->lock, flags);

	if (address <= PM_LEVEL_SIZE(domain->mode) ||
	    WARN_ON_ONCE(domain->mode == PAGE_MODE_6_LEVEL))
		goto out;

	pte = (void *)get_zeroed_page(gfp);
	if (!pte)
		goto out;

	*pte             = PM_LEVEL_PDE(domain->mode,
					iommu_virt_to_phys(domain->pt_root));
	domain->pt_root  = pte;
	domain->mode    += 1;

	ret = true;

out:
	spin_unlock_irqrestore(&domain->lock, flags);

	return ret;
}