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
struct nvkm_vmm {int /*<<< orphan*/  mutex; } ;
struct nvkm_vma {scalar_t__ memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_vmm_unmap_locked (struct nvkm_vmm*,struct nvkm_vma*,int) ; 

void
nvkm_vmm_unmap(struct nvkm_vmm *vmm, struct nvkm_vma *vma)
{
	if (vma->memory) {
		mutex_lock(&vmm->mutex);
		nvkm_vmm_unmap_locked(vmm, vma, false);
		mutex_unlock(&vmm->mutex);
	}
}