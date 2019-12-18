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
struct TYPE_2__ {struct nvkm_client* client; } ;
struct nvkm_uvmm {struct nvkm_vmm* vmm; TYPE_1__ object; } ;
struct nvkm_client {int /*<<< orphan*/  super; } ;
struct nvif_vmm_pfnclr_v0 {scalar_t__ size; scalar_t__ addr; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOSYS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_vmm_pfnclr_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_vmm_pfn_unmap (struct nvkm_vmm*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
nvkm_uvmm_mthd_pfnclr(struct nvkm_uvmm *uvmm, void *argv, u32 argc)
{
	struct nvkm_client *client = uvmm->object.client;
	union {
		struct nvif_vmm_pfnclr_v0 v0;
	} *args = argv;
	struct nvkm_vmm *vmm = uvmm->vmm;
	int ret = -ENOSYS;
	u64 addr, size;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		addr = args->v0.addr;
		size = args->v0.size;
	} else
		return ret;

	if (!client->super)
		return -ENOENT;

	if (size) {
		mutex_lock(&vmm->mutex);
		ret = nvkm_vmm_pfn_unmap(vmm, addr, size);
		mutex_unlock(&vmm->mutex);
	}

	return ret;
}