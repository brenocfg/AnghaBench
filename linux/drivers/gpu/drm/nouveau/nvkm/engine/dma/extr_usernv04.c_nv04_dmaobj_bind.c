#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_memory {int dummy; } ;
typedef  struct nvkm_memory nvkm_gpuobj ;
struct nvkm_dmaobj {int dummy; } ;
struct nvkm_device {TYPE_7__* mmu; } ;
struct TYPE_16__ {int start; int limit; TYPE_3__* dma; } ;
struct nv04_dmaobj {int flags0; int flags2; TYPE_8__ base; scalar_t__ clone; } ;
struct TYPE_15__ {TYPE_6__* vmm; } ;
struct TYPE_14__ {TYPE_5__* pd; } ;
struct TYPE_13__ {TYPE_4__** pt; } ;
struct TYPE_12__ {struct nvkm_memory* memory; } ;
struct TYPE_9__ {struct nvkm_device* device; } ;
struct TYPE_10__ {TYPE_1__ subdev; } ;
struct TYPE_11__ {TYPE_2__ engine; } ;

/* Variables and functions */
 struct nv04_dmaobj* nv04_dmaobj (struct nvkm_dmaobj*) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_memory*) ; 
 int nvkm_gpuobj_new (struct nvkm_device*,int,int,int,struct nvkm_memory*,struct nvkm_memory**) ; 
 int nvkm_gpuobj_wrap (struct nvkm_memory*,struct nvkm_memory**) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_memory*) ; 
 int nvkm_ro32 (struct nvkm_memory*,int) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_memory*,int,int) ; 

__attribute__((used)) static int
nv04_dmaobj_bind(struct nvkm_dmaobj *base, struct nvkm_gpuobj *parent,
		 int align, struct nvkm_gpuobj **pgpuobj)
{
	struct nv04_dmaobj *dmaobj = nv04_dmaobj(base);
	struct nvkm_device *device = dmaobj->base.dma->engine.subdev.device;
	u64 offset = dmaobj->base.start & 0xfffff000;
	u64 adjust = dmaobj->base.start & 0x00000fff;
	u32 length = dmaobj->base.limit - dmaobj->base.start;
	int ret;

	if (dmaobj->clone) {
		struct nvkm_memory *pgt =
			device->mmu->vmm->pd->pt[0]->memory;
		if (!dmaobj->base.start)
			return nvkm_gpuobj_wrap(pgt, pgpuobj);
		nvkm_kmap(pgt);
		offset  = nvkm_ro32(pgt, 8 + (offset >> 10));
		offset &= 0xfffff000;
		nvkm_done(pgt);
	}

	ret = nvkm_gpuobj_new(device, 16, align, false, parent, pgpuobj);
	if (ret == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, dmaobj->flags0 | (adjust << 20));
		nvkm_wo32(*pgpuobj, 0x04, length);
		nvkm_wo32(*pgpuobj, 0x08, dmaobj->flags2 | offset);
		nvkm_wo32(*pgpuobj, 0x0c, dmaobj->flags2 | offset);
		nvkm_done(*pgpuobj);
	}

	return ret;
}