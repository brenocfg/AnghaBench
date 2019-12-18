#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_fifo_chan {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_10__ {int chid; TYPE_4__* inst; } ;
struct gk104_fifo_chan {int runl; int /*<<< orphan*/  killed; int /*<<< orphan*/  head; TYPE_5__ base; struct gk104_fifo* fifo; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_1__ subdev; } ;
struct TYPE_8__ {TYPE_2__ engine; } ;
struct gk104_fifo {TYPE_3__ base; } ;
struct TYPE_9__ {int addr; } ;

/* Variables and functions */
 struct gk104_fifo_chan* gk104_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  gk104_fifo_runlist_insert (struct gk104_fifo*,struct gk104_fifo_chan*) ; 
 int /*<<< orphan*/  gk104_fifo_runlist_update (struct gk104_fifo*,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
gk104_fifo_gpfifo_init(struct nvkm_fifo_chan *base)
{
	struct gk104_fifo_chan *chan = gk104_fifo_chan(base);
	struct gk104_fifo *fifo = chan->fifo;
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	u32 addr = chan->base.inst->addr >> 12;
	u32 coff = chan->base.chid * 8;

	nvkm_mask(device, 0x800004 + coff, 0x000f0000, chan->runl << 16);
	nvkm_wr32(device, 0x800000 + coff, 0x80000000 | addr);

	if (list_empty(&chan->head) && !chan->killed) {
		gk104_fifo_runlist_insert(fifo, chan);
		nvkm_mask(device, 0x800004 + coff, 0x00000400, 0x00000400);
		gk104_fifo_runlist_update(fifo, chan->runl);
		nvkm_mask(device, 0x800004 + coff, 0x00000400, 0x00000400);
	}
}