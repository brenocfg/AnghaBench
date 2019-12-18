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
struct nvkm_vma {int busy; scalar_t__ addr; scalar_t__ size; scalar_t__ refd; int /*<<< orphan*/  mapref; scalar_t__ memory; scalar_t__ mapped; int /*<<< orphan*/  user; } ;
struct TYPE_2__ {struct nvkm_client* client; } ;
struct nvkm_uvmm {struct nvkm_vmm* vmm; TYPE_1__ object; } ;
struct nvkm_memory {int dummy; } ;
struct nvkm_client {int /*<<< orphan*/  super; } ;
struct nvif_vmm_map_v0 {scalar_t__ addr; scalar_t__ size; scalar_t__ memory; scalar_t__ offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSYS ; 
 scalar_t__ IS_ERR (struct nvkm_memory*) ; 
 scalar_t__ NVKM_VMA_PAGE_NONE ; 
 int PTR_ERR (struct nvkm_memory*) ; 
 int /*<<< orphan*/  VMM_DEBUG (struct nvkm_vmm*,char*,int,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_vmm_map_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_memory_map (struct nvkm_memory*,scalar_t__,struct nvkm_vmm*,struct nvkm_vma*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_memory_unref (struct nvkm_memory**) ; 
 struct nvkm_memory* nvkm_umem_search (struct nvkm_client*,scalar_t__) ; 
 struct nvkm_vma* nvkm_vmm_node_search (struct nvkm_vmm*,scalar_t__) ; 
 struct nvkm_vma* nvkm_vmm_node_split (struct nvkm_vmm*,struct nvkm_vma*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_vmm_unmap_region (struct nvkm_vmm*,struct nvkm_vma*) ; 

__attribute__((used)) static int
nvkm_uvmm_mthd_map(struct nvkm_uvmm *uvmm, void *argv, u32 argc)
{
	struct nvkm_client *client = uvmm->object.client;
	union {
		struct nvif_vmm_map_v0 v0;
	} *args = argv;
	u64 addr, size, handle, offset;
	struct nvkm_vmm *vmm = uvmm->vmm;
	struct nvkm_vma *vma;
	struct nvkm_memory *memory;
	int ret = -ENOSYS;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, true))) {
		addr = args->v0.addr;
		size = args->v0.size;
		handle = args->v0.memory;
		offset = args->v0.offset;
	} else
		return ret;

	memory = nvkm_umem_search(client, handle);
	if (IS_ERR(memory)) {
		VMM_DEBUG(vmm, "memory %016llx %ld\n", handle, PTR_ERR(memory));
		return PTR_ERR(memory);
	}

	mutex_lock(&vmm->mutex);
	if (ret = -ENOENT, !(vma = nvkm_vmm_node_search(vmm, addr))) {
		VMM_DEBUG(vmm, "lookup %016llx", addr);
		goto fail;
	}

	if (ret = -ENOENT, (!vma->user && !client->super) || vma->busy) {
		VMM_DEBUG(vmm, "denied %016llx: %d %d %d", addr,
			  vma->user, !client->super, vma->busy);
		goto fail;
	}

	if (ret = -EINVAL, vma->mapped && !vma->memory) {
		VMM_DEBUG(vmm, "pfnmap %016llx", addr);
		goto fail;
	}

	if (ret = -EINVAL, vma->addr != addr || vma->size != size) {
		if (addr + size > vma->addr + vma->size || vma->memory ||
		    (vma->refd == NVKM_VMA_PAGE_NONE && !vma->mapref)) {
			VMM_DEBUG(vmm, "split %d %d %d "
				       "%016llx %016llx %016llx %016llx",
				  !!vma->memory, vma->refd, vma->mapref,
				  addr, size, vma->addr, (u64)vma->size);
			goto fail;
		}

		vma = nvkm_vmm_node_split(vmm, vma, addr, size);
		if (!vma) {
			ret = -ENOMEM;
			goto fail;
		}
	}
	vma->busy = true;
	mutex_unlock(&vmm->mutex);

	ret = nvkm_memory_map(memory, offset, vmm, vma, argv, argc);
	if (ret == 0) {
		/* Successful map will clear vma->busy. */
		nvkm_memory_unref(&memory);
		return 0;
	}

	mutex_lock(&vmm->mutex);
	vma->busy = false;
	nvkm_vmm_unmap_region(vmm, vma);
fail:
	mutex_unlock(&vmm->mutex);
	nvkm_memory_unref(&memory);
	return ret;
}