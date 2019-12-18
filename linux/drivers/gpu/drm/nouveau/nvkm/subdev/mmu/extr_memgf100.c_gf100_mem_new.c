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
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct nvkm_mmu {TYPE_2__ subdev; TYPE_1__* type; } ;
struct nvkm_memory {int dummy; } ;
struct gf100_mem_vn {int dummy; } ;
struct gf100_mem_v0 {int contig; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int ENOSYS ; 
 int NVKM_MEM_COMP ; 
 int NVKM_MEM_DISP ; 
 int NVKM_RAM_MM_MIXED ; 
 int NVKM_RAM_MM_NORMAL ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct gf100_mem_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvif_unvers (int,void**,int /*<<< orphan*/ *,struct gf100_mem_vn) ; 
 int nvkm_ram_get (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct nvkm_memory**) ; 

int
gf100_mem_new(struct nvkm_mmu *mmu, int type, u8 page, u64 size,
	      void *argv, u32 argc, struct nvkm_memory **pmemory)
{
	union {
		struct gf100_mem_vn vn;
		struct gf100_mem_v0 v0;
	} *args = argv;
	int ret = -ENOSYS;
	bool contig;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		contig = args->v0.contig;
	} else
	if (!(ret = nvif_unvers(ret, &argv, &argc, args->vn))) {
		contig = false;
	} else
		return ret;

	if (mmu->type[type].type & (NVKM_MEM_DISP | NVKM_MEM_COMP))
		type = NVKM_RAM_MM_NORMAL;
	else
		type = NVKM_RAM_MM_MIXED;

	return nvkm_ram_get(mmu->subdev.device, type, 0x01, page,
			    size, contig, false, pmemory);
}