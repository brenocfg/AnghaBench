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
typedef  size_t u32 ;
struct imgu_mmu {size_t** l2pts; size_t dummy_page_pteval; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  address_to_pte_idx (unsigned long,size_t*,size_t*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static size_t __imgu_mmu_unmap(struct imgu_mmu *mmu,
			       unsigned long iova, size_t size)
{
	u32 l1pt_idx, l2pt_idx;
	unsigned long flags;
	size_t unmap = size;
	u32 *l2pt;

	if (!mmu)
		return 0;

	address_to_pte_idx(iova, &l1pt_idx, &l2pt_idx);

	spin_lock_irqsave(&mmu->lock, flags);

	l2pt = mmu->l2pts[l1pt_idx];
	if (!l2pt) {
		spin_unlock_irqrestore(&mmu->lock, flags);
		return 0;
	}

	if (l2pt[l2pt_idx] == mmu->dummy_page_pteval)
		unmap = 0;

	l2pt[l2pt_idx] = mmu->dummy_page_pteval;

	spin_unlock_irqrestore(&mmu->lock, flags);

	return unmap;
}