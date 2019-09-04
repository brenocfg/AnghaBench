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
struct nvkm_object {int dummy; } ;
struct nvkm_gpuobj {int dummy; } ;
struct gf100_gr_chan {int mmio_nr; TYPE_4__* mmio_vma; struct gf100_gr* gr; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct gf100_gr {int size; int* data; int /*<<< orphan*/  firmware; TYPE_3__ base; } ;
struct TYPE_8__ {int addr; } ;

/* Variables and functions */
 struct gf100_gr_chan* gf100_gr_chan (struct nvkm_object*) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_gpuobj*) ; 
 int nvkm_gpuobj_new (int /*<<< orphan*/ ,int,int,int,struct nvkm_gpuobj*,struct nvkm_gpuobj**) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_gpuobj*,int,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int
gf100_gr_chan_bind(struct nvkm_object *object, struct nvkm_gpuobj *parent,
		   int align, struct nvkm_gpuobj **pgpuobj)
{
	struct gf100_gr_chan *chan = gf100_gr_chan(object);
	struct gf100_gr *gr = chan->gr;
	int ret, i;

	ret = nvkm_gpuobj_new(gr->base.engine.subdev.device, gr->size,
			      align, false, parent, pgpuobj);
	if (ret)
		return ret;

	nvkm_kmap(*pgpuobj);
	for (i = 0; i < gr->size; i += 4)
		nvkm_wo32(*pgpuobj, i, gr->data[i / 4]);

	if (!gr->firmware) {
		nvkm_wo32(*pgpuobj, 0x00, chan->mmio_nr / 2);
		nvkm_wo32(*pgpuobj, 0x04, chan->mmio_vma->addr >> 8);
	} else {
		nvkm_wo32(*pgpuobj, 0xf4, 0);
		nvkm_wo32(*pgpuobj, 0xf8, 0);
		nvkm_wo32(*pgpuobj, 0x10, chan->mmio_nr / 2);
		nvkm_wo32(*pgpuobj, 0x14, lower_32_bits(chan->mmio_vma->addr));
		nvkm_wo32(*pgpuobj, 0x18, upper_32_bits(chan->mmio_vma->addr));
		nvkm_wo32(*pgpuobj, 0x1c, 1);
		nvkm_wo32(*pgpuobj, 0x20, 0);
		nvkm_wo32(*pgpuobj, 0x28, 0);
		nvkm_wo32(*pgpuobj, 0x2c, 0);
	}
	nvkm_done(*pgpuobj);
	return 0;
}