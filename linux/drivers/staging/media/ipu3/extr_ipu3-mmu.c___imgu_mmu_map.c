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
struct imgu_mmu {size_t dummy_page_pteval; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 size_t IPU3_ADDR2PTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  address_to_pte_idx (unsigned long,size_t*,size_t*) ; 
 size_t* imgu_mmu_get_l2pt (struct imgu_mmu*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __imgu_mmu_map(struct imgu_mmu *mmu, unsigned long iova,
			  phys_addr_t paddr)
{
	u32 l1pt_idx, l2pt_idx;
	unsigned long flags;
	u32 *l2pt;

	if (!mmu)
		return -ENODEV;

	address_to_pte_idx(iova, &l1pt_idx, &l2pt_idx);

	l2pt = imgu_mmu_get_l2pt(mmu, l1pt_idx);
	if (!l2pt)
		return -ENOMEM;

	spin_lock_irqsave(&mmu->lock, flags);

	if (l2pt[l2pt_idx] != mmu->dummy_page_pteval) {
		spin_unlock_irqrestore(&mmu->lock, flags);
		return -EBUSY;
	}

	l2pt[l2pt_idx] = IPU3_ADDR2PTE(paddr);

	spin_unlock_irqrestore(&mmu->lock, flags);

	return 0;
}