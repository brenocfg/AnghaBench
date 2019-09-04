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
typedef  int /*<<< orphan*/  uint32_t ;
struct psb_mmu_pt {scalar_t__ count; size_t index; int /*<<< orphan*/ * v; struct psb_mmu_pd* pd; } ;
struct psb_mmu_pd {int hw_context; TYPE_1__* driver; int /*<<< orphan*/ ** tables; int /*<<< orphan*/  invalid_pde; int /*<<< orphan*/  p; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  needs_tlbflush; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_mmu_clflush (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  psb_mmu_free_pt (struct psb_mmu_pt*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psb_mmu_pt_unmap_unlock(struct psb_mmu_pt *pt)
{
	struct psb_mmu_pd *pd = pt->pd;
	uint32_t *v;

	kunmap_atomic(pt->v);
	if (pt->count == 0) {
		v = kmap_atomic(pd->p);
		v[pt->index] = pd->invalid_pde;
		pd->tables[pt->index] = NULL;

		if (pd->hw_context != -1) {
			psb_mmu_clflush(pd->driver, (void *)&v[pt->index]);
			atomic_set(&pd->driver->needs_tlbflush, 1);
		}
		kunmap_atomic(v);
		spin_unlock(&pd->driver->lock);
		psb_mmu_free_pt(pt);
		return;
	}
	spin_unlock(&pd->driver->lock);
}