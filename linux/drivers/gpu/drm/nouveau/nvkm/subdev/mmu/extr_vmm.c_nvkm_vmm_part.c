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
struct nvkm_vmm {int /*<<< orphan*/  mutex; TYPE_1__* func; } ;
struct nvkm_memory {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* part ) (struct nvkm_vmm*,struct nvkm_memory*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_vmm*,struct nvkm_memory*) ; 

void
nvkm_vmm_part(struct nvkm_vmm *vmm, struct nvkm_memory *inst)
{
	if (inst && vmm && vmm->func->part) {
		mutex_lock(&vmm->mutex);
		vmm->func->part(vmm, inst);
		mutex_unlock(&vmm->mutex);
	}
}