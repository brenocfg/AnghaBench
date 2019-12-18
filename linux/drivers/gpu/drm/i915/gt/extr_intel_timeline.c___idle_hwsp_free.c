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
struct intel_timeline_hwsp {unsigned long long free_bitmap; int /*<<< orphan*/  free_link; int /*<<< orphan*/  vma; struct intel_gt_timelines* gt_timelines; } ;
struct intel_gt_timelines {int /*<<< orphan*/  hwsp_lock; int /*<<< orphan*/  hwsp_free_list; } ;

/* Variables and functions */
 int BITS_PER_TYPE (unsigned long long) ; 
 unsigned long long BIT_ULL (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_vma_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct intel_timeline_hwsp*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __idle_hwsp_free(struct intel_timeline_hwsp *hwsp, int cacheline)
{
	struct intel_gt_timelines *gt = hwsp->gt_timelines;
	unsigned long flags;

	spin_lock_irqsave(&gt->hwsp_lock, flags);

	/* As a cacheline becomes available, publish the HWSP on the freelist */
	if (!hwsp->free_bitmap)
		list_add_tail(&hwsp->free_link, &gt->hwsp_free_list);

	GEM_BUG_ON(cacheline >= BITS_PER_TYPE(hwsp->free_bitmap));
	hwsp->free_bitmap |= BIT_ULL(cacheline);

	/* And if no one is left using it, give the page back to the system */
	if (hwsp->free_bitmap == ~0ull) {
		i915_vma_put(hwsp->vma);
		list_del(&hwsp->free_link);
		kfree(hwsp);
	}

	spin_unlock_irqrestore(&gt->hwsp_lock, flags);
}