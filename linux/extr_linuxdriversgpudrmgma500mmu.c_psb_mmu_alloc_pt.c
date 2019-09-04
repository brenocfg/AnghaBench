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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct psb_mmu_pt {scalar_t__ index; struct psb_mmu_pd* pd; scalar_t__ count; int /*<<< orphan*/  p; } ;
struct psb_mmu_pd {int /*<<< orphan*/  invalid_pte; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int clflush_add; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_DMA32 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct psb_mmu_pt*) ; 
 struct psb_mmu_pt* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct psb_mmu_pt *psb_mmu_alloc_pt(struct psb_mmu_pd *pd)
{
	struct psb_mmu_pt *pt = kmalloc(sizeof(*pt), GFP_KERNEL);
	void *v;
	uint32_t clflush_add = pd->driver->clflush_add >> PAGE_SHIFT;
	uint32_t clflush_count = PAGE_SIZE / clflush_add;
	spinlock_t *lock = &pd->driver->lock;
	uint8_t *clf;
	uint32_t *ptes;
	int i;

	if (!pt)
		return NULL;

	pt->p = alloc_page(GFP_DMA32);
	if (!pt->p) {
		kfree(pt);
		return NULL;
	}

	spin_lock(lock);

	v = kmap_atomic(pt->p);
	clf = (uint8_t *) v;
	ptes = (uint32_t *) v;
	for (i = 0; i < (PAGE_SIZE / sizeof(uint32_t)); ++i)
		*ptes++ = pd->invalid_pte;

#if defined(CONFIG_X86)
	if (pd->driver->has_clflush && pd->hw_context != -1) {
		mb();
		for (i = 0; i < clflush_count; ++i) {
			psb_clflush(clf);
			clf += clflush_add;
		}
		mb();
	}
#endif
	kunmap_atomic(v);
	spin_unlock(lock);

	pt->count = 0;
	pt->pd = pd;
	pt->index = 0;

	return pt;
}