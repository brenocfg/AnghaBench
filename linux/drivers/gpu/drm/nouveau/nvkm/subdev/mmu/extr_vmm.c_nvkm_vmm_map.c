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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm_map {int dummy; } ;
struct nvkm_vmm {int /*<<< orphan*/  mutex; } ;
struct nvkm_vma {int busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvkm_vmm_map_locked (struct nvkm_vmm*,struct nvkm_vma*,void*,int /*<<< orphan*/ ,struct nvkm_vmm_map*) ; 

int
nvkm_vmm_map(struct nvkm_vmm *vmm, struct nvkm_vma *vma, void *argv, u32 argc,
	     struct nvkm_vmm_map *map)
{
	int ret;
	mutex_lock(&vmm->mutex);
	ret = nvkm_vmm_map_locked(vmm, vma, argv, argc, map);
	vma->busy = false;
	mutex_unlock(&vmm->mutex);
	return ret;
}