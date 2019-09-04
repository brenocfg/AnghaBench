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
typedef  int u32 ;
struct nvkm_fifo_chan {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_5__ {int chid; } ;
struct gf100_fifo_chan {int /*<<< orphan*/  killed; int /*<<< orphan*/  head; TYPE_1__ base; struct gf100_fifo* fifo; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_2__ subdev; } ;
struct TYPE_8__ {TYPE_3__ engine; } ;
struct gf100_fifo {TYPE_4__ base; } ;

/* Variables and functions */
 struct gf100_fifo_chan* gf100_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  gf100_fifo_intr_engine (struct gf100_fifo*) ; 
 int /*<<< orphan*/  gf100_fifo_runlist_commit (struct gf100_fifo*) ; 
 int /*<<< orphan*/  gf100_fifo_runlist_remove (struct gf100_fifo*,struct gf100_fifo_chan*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gf100_fifo_gpfifo_fini(struct nvkm_fifo_chan *base)
{
	struct gf100_fifo_chan *chan = gf100_fifo_chan(base);
	struct gf100_fifo *fifo = chan->fifo;
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	u32 coff = chan->base.chid * 8;

	if (!list_empty(&chan->head) && !chan->killed) {
		gf100_fifo_runlist_remove(fifo, chan);
		nvkm_mask(device, 0x003004 + coff, 0x00000001, 0x00000000);
		gf100_fifo_runlist_commit(fifo);
	}

	gf100_fifo_intr_engine(fifo);

	nvkm_wr32(device, 0x003000 + coff, 0x00000000);
}