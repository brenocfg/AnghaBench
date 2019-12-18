#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_mmu_pt {int /*<<< orphan*/  memory; TYPE_2__* ptc; int /*<<< orphan*/  head; scalar_t__ sub; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct nvkm_mmu {TYPE_3__ ptc; TYPE_1__ ptp; } ;
struct TYPE_5__ {int refs; int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvkm_mmu_pt*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_memory_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_mmu_ptp_put (struct nvkm_mmu*,int,struct nvkm_mmu_pt*) ; 

void
nvkm_mmu_ptc_put(struct nvkm_mmu *mmu, bool force, struct nvkm_mmu_pt **ppt)
{
	struct nvkm_mmu_pt *pt = *ppt;
	if (pt) {
		/* Handle sub-allocated page tables. */
		if (pt->sub) {
			mutex_lock(&mmu->ptp.mutex);
			nvkm_mmu_ptp_put(mmu, force, pt);
			mutex_unlock(&mmu->ptp.mutex);
			return;
		}

		/* Either cache or free the object. */
		mutex_lock(&mmu->ptc.mutex);
		if (pt->ptc->refs < 8 /* Heuristic. */ && !force) {
			list_add_tail(&pt->head, &pt->ptc->item);
			pt->ptc->refs++;
		} else {
			nvkm_memory_unref(&pt->memory);
			kfree(pt);
		}
		mutex_unlock(&mmu->ptc.mutex);
	}
}