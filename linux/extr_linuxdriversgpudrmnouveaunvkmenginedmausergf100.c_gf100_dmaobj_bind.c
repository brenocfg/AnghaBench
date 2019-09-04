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
struct nvkm_gpuobj {int dummy; } ;
struct nvkm_dmaobj {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  start; int /*<<< orphan*/  limit; TYPE_3__* dma; } ;
struct gf100_dmaobj {int flags0; int flags5; TYPE_4__ base; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;

/* Variables and functions */
 struct gf100_dmaobj* gf100_dmaobj (struct nvkm_dmaobj*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_gpuobj*) ; 
 int nvkm_gpuobj_new (struct nvkm_device*,int,int,int,struct nvkm_gpuobj*,struct nvkm_gpuobj**) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_gpuobj*,int,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gf100_dmaobj_bind(struct nvkm_dmaobj *base, struct nvkm_gpuobj *parent,
		  int align, struct nvkm_gpuobj **pgpuobj)
{
	struct gf100_dmaobj *dmaobj = gf100_dmaobj(base);
	struct nvkm_device *device = dmaobj->base.dma->engine.subdev.device;
	int ret;

	ret = nvkm_gpuobj_new(device, 24, align, false, parent, pgpuobj);
	if (ret == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, dmaobj->flags0);
		nvkm_wo32(*pgpuobj, 0x04, lower_32_bits(dmaobj->base.limit));
		nvkm_wo32(*pgpuobj, 0x08, lower_32_bits(dmaobj->base.start));
		nvkm_wo32(*pgpuobj, 0x0c, upper_32_bits(dmaobj->base.limit) << 24 |
					  upper_32_bits(dmaobj->base.start));
		nvkm_wo32(*pgpuobj, 0x10, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x14, dmaobj->flags5);
		nvkm_done(*pgpuobj);
	}

	return ret;
}