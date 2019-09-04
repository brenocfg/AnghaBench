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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct nvkm_mmu {TYPE_1__ subdev; TYPE_2__* type; } ;
struct nvkm_memory {int dummy; } ;
struct nv04_mem_vn {int dummy; } ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
 int ENOSYS ; 
 int NVKM_MEM_MAPPABLE ; 
 int NVKM_RAM_MM_NOMAP ; 
 int NVKM_RAM_MM_NORMAL ; 
 int nvif_unvers (int,void**,int /*<<< orphan*/ *,struct nv04_mem_vn) ; 
 int nvkm_ram_get (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct nvkm_memory**) ; 

int
nv04_mem_new(struct nvkm_mmu *mmu, int type, u8 page, u64 size,
	     void *argv, u32 argc, struct nvkm_memory **pmemory)
{
	union {
		struct nv04_mem_vn vn;
	} *args = argv;
	int ret = -ENOSYS;

	if ((ret = nvif_unvers(ret, &argv, &argc, args->vn)))
		return ret;

	if (mmu->type[type].type & NVKM_MEM_MAPPABLE)
		type = NVKM_RAM_MM_NORMAL;
	else
		type = NVKM_RAM_MM_NOMAP;

	return nvkm_ram_get(mmu->subdev.device, type, 0x01, page,
			    size, true, false, pmemory);
}