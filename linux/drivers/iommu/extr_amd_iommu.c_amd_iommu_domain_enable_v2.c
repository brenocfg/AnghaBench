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
struct protection_domain {scalar_t__ dev_cnt; int flags; int glx; int /*<<< orphan*/  lock; int /*<<< orphan*/ * gcr3_tbl; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PASID_MASK ; 
 int PD_IOMMUV2_MASK ; 
 int amd_iommu_max_glx_val ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct protection_domain* to_pdomain (struct iommu_domain*) ; 
 int /*<<< orphan*/  update_domain (struct protection_domain*) ; 

int amd_iommu_domain_enable_v2(struct iommu_domain *dom, int pasids)
{
	struct protection_domain *domain = to_pdomain(dom);
	unsigned long flags;
	int levels, ret;

	if (pasids <= 0 || pasids > (PASID_MASK + 1))
		return -EINVAL;

	/* Number of GCR3 table levels required */
	for (levels = 0; (pasids - 1) & ~0x1ff; pasids >>= 9)
		levels += 1;

	if (levels > amd_iommu_max_glx_val)
		return -EINVAL;

	spin_lock_irqsave(&domain->lock, flags);

	/*
	 * Save us all sanity checks whether devices already in the
	 * domain support IOMMUv2. Just force that the domain has no
	 * devices attached when it is switched into IOMMUv2 mode.
	 */
	ret = -EBUSY;
	if (domain->dev_cnt > 0 || domain->flags & PD_IOMMUV2_MASK)
		goto out;

	ret = -ENOMEM;
	domain->gcr3_tbl = (void *)get_zeroed_page(GFP_ATOMIC);
	if (domain->gcr3_tbl == NULL)
		goto out;

	domain->glx      = levels;
	domain->flags   |= PD_IOMMUV2_MASK;

	update_domain(domain);

	ret = 0;

out:
	spin_unlock_irqrestore(&domain->lock, flags);

	return ret;
}