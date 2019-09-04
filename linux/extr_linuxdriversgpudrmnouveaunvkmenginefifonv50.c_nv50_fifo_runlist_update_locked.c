#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_memory {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_2__ subdev; } ;
struct TYPE_4__ {int nr; TYPE_3__ engine; } ;
struct nv50_fifo {size_t cur_runlist; TYPE_1__ base; struct nvkm_memory** runlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_done (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_memory*) ; 
 int nvkm_memory_addr (struct nvkm_memory*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_memory*,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv50_fifo_runlist_update_locked(struct nv50_fifo *fifo)
{
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	struct nvkm_memory *cur;
	int i, p;

	cur = fifo->runlist[fifo->cur_runlist];
	fifo->cur_runlist = !fifo->cur_runlist;

	nvkm_kmap(cur);
	for (i = 0, p = 0; i < fifo->base.nr; i++) {
		if (nvkm_rd32(device, 0x002600 + (i * 4)) & 0x80000000)
			nvkm_wo32(cur, p++ * 4, i);
	}
	nvkm_done(cur);

	nvkm_wr32(device, 0x0032f4, nvkm_memory_addr(cur) >> 12);
	nvkm_wr32(device, 0x0032ec, p);
	nvkm_wr32(device, 0x002500, 0x00000101);
}