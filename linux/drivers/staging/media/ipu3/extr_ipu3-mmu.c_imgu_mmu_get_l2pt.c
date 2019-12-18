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
struct imgu_mmu {size_t** l2pts; size_t* l1pt; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  dummy_page_pteval; } ;

/* Variables and functions */
 size_t IPU3_ADDR2PTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t*,size_t) ; 
 size_t* imgu_mmu_alloc_page_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_mmu_free_page_table (size_t*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_to_phys (size_t*) ; 

__attribute__((used)) static u32 *imgu_mmu_get_l2pt(struct imgu_mmu *mmu, u32 l1pt_idx)
{
	unsigned long flags;
	u32 *l2pt, *new_l2pt;
	u32 pteval;

	spin_lock_irqsave(&mmu->lock, flags);

	l2pt = mmu->l2pts[l1pt_idx];
	if (l2pt)
		goto done;

	spin_unlock_irqrestore(&mmu->lock, flags);

	new_l2pt = imgu_mmu_alloc_page_table(mmu->dummy_page_pteval);
	if (!new_l2pt)
		return NULL;

	spin_lock_irqsave(&mmu->lock, flags);

	dev_dbg(mmu->dev, "allocated page table %p for l1pt_idx %u\n",
		new_l2pt, l1pt_idx);

	l2pt = mmu->l2pts[l1pt_idx];
	if (l2pt) {
		imgu_mmu_free_page_table(new_l2pt);
		goto done;
	}

	l2pt = new_l2pt;
	mmu->l2pts[l1pt_idx] = new_l2pt;

	pteval = IPU3_ADDR2PTE(virt_to_phys(new_l2pt));
	mmu->l1pt[l1pt_idx] = pteval;

done:
	spin_unlock_irqrestore(&mmu->lock, flags);
	return l2pt;
}