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
typedef  int /*<<< orphan*/  uvmm ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_vma {scalar_t__ size; scalar_t__ addr; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct nvkm_mmu {TYPE_1__ subdev; } ;
struct nvkm_memory {int dummy; } ;
struct nvkm_device {TYPE_2__* func; } ;
struct gf100_vmm_map_v0 {int /*<<< orphan*/  kind; int /*<<< orphan*/  ro; } ;
struct gf100_mem_map_vn {int dummy; } ;
struct gf100_mem_map_v0 {int /*<<< orphan*/  kind; int /*<<< orphan*/  ro; } ;
struct TYPE_4__ {scalar_t__ (* resource_addr ) (struct nvkm_device*,int) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct gf100_mem_map_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvif_unvers (int,void**,int /*<<< orphan*/ *,struct gf100_mem_map_vn) ; 
 struct nvkm_vmm* nvkm_bar_bar1_vmm (struct nvkm_device*) ; 
 int nvkm_memory_map (struct nvkm_memory*,int /*<<< orphan*/ ,struct nvkm_vmm*,struct nvkm_vma*,struct gf100_vmm_map_v0*,int) ; 
 int /*<<< orphan*/  nvkm_memory_page (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_memory_size (struct nvkm_memory*) ; 
 int nvkm_vmm_get (struct nvkm_vmm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_vma**) ; 
 scalar_t__ stub1 (struct nvkm_device*,int) ; 

int
gf100_mem_map(struct nvkm_mmu *mmu, struct nvkm_memory *memory, void *argv,
	      u32 argc, u64 *paddr, u64 *psize, struct nvkm_vma **pvma)
{
	struct gf100_vmm_map_v0 uvmm = {};
	union {
		struct gf100_mem_map_vn vn;
		struct gf100_mem_map_v0 v0;
	} *args = argv;
	struct nvkm_device *device = mmu->subdev.device;
	struct nvkm_vmm *bar = nvkm_bar_bar1_vmm(device);
	int ret = -ENOSYS;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		uvmm.ro   = args->v0.ro;
		uvmm.kind = args->v0.kind;
	} else
	if (!(ret = nvif_unvers(ret, &argv, &argc, args->vn))) {
	} else
		return ret;

	ret = nvkm_vmm_get(bar, nvkm_memory_page(memory),
				nvkm_memory_size(memory), pvma);
	if (ret)
		return ret;

	ret = nvkm_memory_map(memory, 0, bar, *pvma, &uvmm, sizeof(uvmm));
	if (ret)
		return ret;

	*paddr = device->func->resource_addr(device, 1) + (*pvma)->addr;
	*psize = (*pvma)->size;
	return 0;
}