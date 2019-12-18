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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm_map {TYPE_2__* page; } ;
struct nvkm_vmm {TYPE_1__* func; } ;
struct nvkm_vma {int dummy; } ;
struct TYPE_4__ {scalar_t__ shift; } ;
struct TYPE_3__ {TYPE_2__* page; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VMM_DEBUG (struct nvkm_vmm*,char*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_vmm_map_valid (struct nvkm_vmm*,struct nvkm_vma*,void*,int /*<<< orphan*/ ,struct nvkm_vmm_map*) ; 

__attribute__((used)) static int
nvkm_vmm_map_choose(struct nvkm_vmm *vmm, struct nvkm_vma *vma,
		    void *argv, u32 argc, struct nvkm_vmm_map *map)
{
	for (map->page = vmm->func->page; map->page->shift; map->page++) {
		VMM_DEBUG(vmm, "trying %d", map->page->shift);
		if (!nvkm_vmm_map_valid(vmm, vma, argv, argc, map))
			return 0;
	}
	return -EINVAL;
}