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
struct TYPE_8__ {int chid; TYPE_2__* inst; } ;
struct gf100_fifo_chan {int /*<<< orphan*/  killed; int /*<<< orphan*/  head; TYPE_3__ base; struct gf100_fifo* fifo; } ;
struct TYPE_9__ {struct nvkm_device* device; } ;
struct TYPE_10__ {TYPE_4__ subdev; } ;
struct TYPE_6__ {TYPE_5__ engine; } ;
struct gf100_fifo {TYPE_1__ base; } ;
struct TYPE_7__ {int addr; } ;

/* Variables and functions */
 struct gf100_fifo_chan* gf100_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  gf100_fifo_runlist_commit (struct gf100_fifo*) ; 
 int /*<<< orphan*/  gf100_fifo_runlist_insert (struct gf100_fifo*,struct gf100_fifo_chan*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gf100_fifo_gpfifo_init(struct nvkm_fifo_chan *base)
{
	struct gf100_fifo_chan *chan = gf100_fifo_chan(base);
	struct gf100_fifo *fifo = chan->fifo;
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	u32 addr = chan->base.inst->addr >> 12;
	u32 coff = chan->base.chid * 8;

	nvkm_wr32(device, 0x003000 + coff, 0xc0000000 | addr);

	if (list_empty(&chan->head) && !chan->killed) {
		gf100_fifo_runlist_insert(fifo, chan);
		nvkm_wr32(device, 0x003004 + coff, 0x001f0001);
		gf100_fifo_runlist_commit(fifo);
	}
}