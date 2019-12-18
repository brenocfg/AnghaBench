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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm {int /*<<< orphan*/  mutex; } ;
struct nvkm_vma {scalar_t__ addr; int /*<<< orphan*/  memory; scalar_t__ busy; int /*<<< orphan*/  user; } ;
struct TYPE_2__ {struct nvkm_client* client; } ;
struct nvkm_uvmm {struct nvkm_vmm* vmm; TYPE_1__ object; } ;
struct nvkm_client {int /*<<< orphan*/  super; } ;
struct nvif_vmm_unmap_v0 {scalar_t__ addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOSYS ; 
 int /*<<< orphan*/  VMM_DEBUG (struct nvkm_vmm*,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_vmm_unmap_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nvkm_vma* nvkm_vmm_node_search (struct nvkm_vmm*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_vmm_unmap_locked (struct nvkm_vmm*,struct nvkm_vma*,int) ; 

__attribute__((used)) static int
nvkm_uvmm_mthd_unmap(struct nvkm_uvmm *uvmm, void *argv, u32 argc)
{
	struct nvkm_client *client = uvmm->object.client;
	union {
		struct nvif_vmm_unmap_v0 v0;
	} *args = argv;
	struct nvkm_vmm *vmm = uvmm->vmm;
	struct nvkm_vma *vma;
	int ret = -ENOSYS;
	u64 addr;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		addr = args->v0.addr;
	} else
		return ret;

	mutex_lock(&vmm->mutex);
	vma = nvkm_vmm_node_search(vmm, addr);
	if (ret = -ENOENT, !vma || vma->addr != addr) {
		VMM_DEBUG(vmm, "lookup %016llx: %016llx",
			  addr, vma ? vma->addr : ~0ULL);
		goto done;
	}

	if (ret = -ENOENT, (!vma->user && !client->super) || vma->busy) {
		VMM_DEBUG(vmm, "denied %016llx: %d %d %d", addr,
			  vma->user, !client->super, vma->busy);
		goto done;
	}

	if (ret = -EINVAL, !vma->memory) {
		VMM_DEBUG(vmm, "unmapped");
		goto done;
	}

	nvkm_vmm_unmap_locked(vmm, vma, false);
	ret = 0;
done:
	mutex_unlock(&vmm->mutex);
	return ret;
}