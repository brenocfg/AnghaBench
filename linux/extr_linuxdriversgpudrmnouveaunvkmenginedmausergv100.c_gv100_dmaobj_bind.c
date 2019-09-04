#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct nvkm_gpuobj {int dummy; } ;
struct nvkm_dmaobj {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {int start; int limit; TYPE_3__* dma; } ;
struct gv100_dmaobj {int /*<<< orphan*/  flags0; TYPE_4__ base; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;

/* Variables and functions */
 struct gv100_dmaobj* gv100_dmaobj (struct nvkm_dmaobj*) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_gpuobj*) ; 
 int nvkm_gpuobj_new (struct nvkm_device*,int,int,int,struct nvkm_gpuobj*,struct nvkm_gpuobj**) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_gpuobj*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static int
gv100_dmaobj_bind(struct nvkm_dmaobj *base, struct nvkm_gpuobj *parent,
		  int align, struct nvkm_gpuobj **pgpuobj)
{
	struct gv100_dmaobj *dmaobj = gv100_dmaobj(base);
	struct nvkm_device *device = dmaobj->base.dma->engine.subdev.device;
	u64 start = dmaobj->base.start >> 8;
	u64 limit = dmaobj->base.limit >> 8;
	int ret;

	ret = nvkm_gpuobj_new(device, 24, align, false, parent, pgpuobj);
	if (ret == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, dmaobj->flags0);
		nvkm_wo32(*pgpuobj, 0x04, lower_32_bits(start));
		nvkm_wo32(*pgpuobj, 0x08, upper_32_bits(start));
		nvkm_wo32(*pgpuobj, 0x0c, lower_32_bits(limit));
		nvkm_wo32(*pgpuobj, 0x10, upper_32_bits(limit));
		nvkm_done(*pgpuobj);
	}

	return ret;
}