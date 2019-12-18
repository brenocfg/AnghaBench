#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_vmm_iter {scalar_t__ flush; TYPE_2__* vmm; } ;
struct TYPE_4__ {TYPE_1__* func; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* flush ) (TYPE_2__*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ NVKM_VMM_LEVELS_MAX ; 
 int /*<<< orphan*/  TRA (struct nvkm_vmm_iter*,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static inline void
nvkm_vmm_flush(struct nvkm_vmm_iter *it)
{
	if (it->flush != NVKM_VMM_LEVELS_MAX) {
		if (it->vmm->func->flush) {
			TRA(it, "flush: %d", it->flush);
			it->vmm->func->flush(it->vmm, it->flush);
		}
		it->flush = NVKM_VMM_LEVELS_MAX;
	}
}