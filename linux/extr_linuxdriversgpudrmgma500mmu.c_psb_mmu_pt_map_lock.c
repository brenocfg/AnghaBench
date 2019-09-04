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
typedef  size_t uint32_t ;
struct psb_mmu_pt {int /*<<< orphan*/  p; int /*<<< orphan*/  v; } ;
struct psb_mmu_pd {struct psb_mmu_pt** tables; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmap_atomic (int /*<<< orphan*/ ) ; 
 size_t psb_mmu_pd_index (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct psb_mmu_pt *psb_mmu_pt_map_lock(struct psb_mmu_pd *pd,
					      unsigned long addr)
{
	uint32_t index = psb_mmu_pd_index(addr);
	struct psb_mmu_pt *pt;
	spinlock_t *lock = &pd->driver->lock;

	spin_lock(lock);
	pt = pd->tables[index];
	if (!pt) {
		spin_unlock(lock);
		return NULL;
	}
	pt->v = kmap_atomic(pt->p);
	return pt;
}