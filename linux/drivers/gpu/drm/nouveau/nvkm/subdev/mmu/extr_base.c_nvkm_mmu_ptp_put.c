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
struct nvkm_mmu_ptp {int base; int shift; int /*<<< orphan*/  head; int /*<<< orphan*/  pt; int /*<<< orphan*/  mask; int /*<<< orphan*/  free; struct nvkm_mmu_ptp* ptp; } ;
struct nvkm_mmu_pt {int base; int shift; int /*<<< orphan*/  head; int /*<<< orphan*/  pt; int /*<<< orphan*/  mask; int /*<<< orphan*/  free; struct nvkm_mmu_pt* ptp; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct nvkm_mmu {TYPE_1__ ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int const) ; 
 int /*<<< orphan*/  kfree (struct nvkm_mmu_ptp*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_mmu_ptc_put (struct nvkm_mmu*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvkm_mmu_ptp_put(struct nvkm_mmu *mmu, bool force, struct nvkm_mmu_pt *pt)
{
	const int slot = pt->base >> pt->ptp->shift;
	struct nvkm_mmu_ptp *ptp = pt->ptp;

	/* If there were no free slots in the parent allocation before,
	 * there will be now, so return PTP to the cache.
	 */
	if (!ptp->free)
		list_add(&ptp->head, &mmu->ptp.list);
	ptp->free |= BIT(slot);

	/* If there's no more sub-allocations, destroy PTP. */
	if (ptp->free == ptp->mask) {
		nvkm_mmu_ptc_put(mmu, force, &ptp->pt);
		list_del(&ptp->head);
		kfree(ptp);
	}

	kfree(pt);
}