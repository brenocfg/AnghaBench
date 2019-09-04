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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm {int /*<<< orphan*/  mutex; } ;
struct nvkm_vma {int user; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {struct nvkm_client* client; } ;
struct nvkm_uvmm {struct nvkm_vmm* vmm; TYPE_1__ object; } ;
struct nvkm_client {int /*<<< orphan*/  super; } ;
struct nvif_vmm_get_v0 {scalar_t__ type; int sparse; int /*<<< orphan*/  addr; int /*<<< orphan*/  size; int /*<<< orphan*/  align; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int ENOSYS ; 
 scalar_t__ NVIF_VMM_GET_V0_ADDR ; 
 scalar_t__ NVIF_VMM_GET_V0_PTES ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_vmm_get_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_vmm_get_locked (struct nvkm_vmm*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_vma**) ; 

__attribute__((used)) static int
nvkm_uvmm_mthd_get(struct nvkm_uvmm *uvmm, void *argv, u32 argc)
{
	struct nvkm_client *client = uvmm->object.client;
	union {
		struct nvif_vmm_get_v0 v0;
	} *args = argv;
	struct nvkm_vmm *vmm = uvmm->vmm;
	struct nvkm_vma *vma;
	int ret = -ENOSYS;
	bool getref, mapref, sparse;
	u8 page, align;
	u64 size;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		getref = args->v0.type == NVIF_VMM_GET_V0_PTES;
		mapref = args->v0.type == NVIF_VMM_GET_V0_ADDR;
		sparse = args->v0.sparse;
		page = args->v0.page;
		align = args->v0.align;
		size = args->v0.size;
	} else
		return ret;

	mutex_lock(&vmm->mutex);
	ret = nvkm_vmm_get_locked(vmm, getref, mapref, sparse,
				  page, align, size, &vma);
	mutex_unlock(&vmm->mutex);
	if (ret)
		return ret;

	args->v0.addr = vma->addr;
	vma->user = !client->super;
	return ret;
}