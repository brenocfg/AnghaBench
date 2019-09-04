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
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_fifo_chan {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_10__ {int chid; } ;
struct nv50_fifo_chan {TYPE_5__ base; TYPE_4__* ramfc; struct nv50_fifo* fifo; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_1__ subdev; } ;
struct TYPE_8__ {TYPE_2__ engine; } ;
struct nv50_fifo {TYPE_3__ base; } ;
struct TYPE_9__ {int addr; } ;

/* Variables and functions */
 struct nv50_fifo_chan* nv50_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  nv50_fifo_runlist_update (struct nv50_fifo*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv50_fifo_chan_init(struct nvkm_fifo_chan *base)
{
	struct nv50_fifo_chan *chan = nv50_fifo_chan(base);
	struct nv50_fifo *fifo = chan->fifo;
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	u64 addr = chan->ramfc->addr >> 12;
	u32 chid = chan->base.chid;

	nvkm_wr32(device, 0x002600 + (chid * 4), 0x80000000 | addr);
	nv50_fifo_runlist_update(fifo);
}