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
typedef  unsigned long uint32_t ;
struct psb_mmu_pt {unsigned long* v; } ;
struct psb_mmu_pd {unsigned long invalid_pde; unsigned long invalid_pte; TYPE_1__* driver; int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  sem; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PSB_PTE_VALID ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 unsigned long* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned long*) ; 
 size_t psb_mmu_pd_index (unsigned long) ; 
 size_t psb_mmu_pt_index (unsigned long) ; 
 struct psb_mmu_pt* psb_mmu_pt_map_lock (struct psb_mmu_pd*,unsigned long) ; 
 int /*<<< orphan*/  psb_mmu_pt_unmap_unlock (struct psb_mmu_pt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int psb_mmu_virtual_to_pfn(struct psb_mmu_pd *pd, uint32_t virtual,
			   unsigned long *pfn)
{
	int ret;
	struct psb_mmu_pt *pt;
	uint32_t tmp;
	spinlock_t *lock = &pd->driver->lock;

	down_read(&pd->driver->sem);
	pt = psb_mmu_pt_map_lock(pd, virtual);
	if (!pt) {
		uint32_t *v;

		spin_lock(lock);
		v = kmap_atomic(pd->p);
		tmp = v[psb_mmu_pd_index(virtual)];
		kunmap_atomic(v);
		spin_unlock(lock);

		if (tmp != pd->invalid_pde || !(tmp & PSB_PTE_VALID) ||
		    !(pd->invalid_pte & PSB_PTE_VALID)) {
			ret = -EINVAL;
			goto out;
		}
		ret = 0;
		*pfn = pd->invalid_pte >> PAGE_SHIFT;
		goto out;
	}
	tmp = pt->v[psb_mmu_pt_index(virtual)];
	if (!(tmp & PSB_PTE_VALID)) {
		ret = -EINVAL;
	} else {
		ret = 0;
		*pfn = tmp >> PAGE_SHIFT;
	}
	psb_mmu_pt_unmap_unlock(pt);
out:
	up_read(&pd->driver->sem);
	return ret;
}