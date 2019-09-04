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
struct nvkm_memory {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct nvkm_device {TYPE_3__* imem; } ;
struct nv04_fifo_ramfc {unsigned long long bits; unsigned long long regs; unsigned long long ctxs; int ctxp; int /*<<< orphan*/  regp; } ;
struct TYPE_9__ {int chid; } ;
struct nv04_fifo_chan {int ramfc; TYPE_4__ base; struct nv04_fifo* fifo; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_1__ subdev; } ;
struct TYPE_10__ {int nr; int /*<<< orphan*/  lock; TYPE_2__ engine; } ;
struct nv04_fifo {TYPE_5__ base; struct nv04_fifo_ramfc* ramfc; } ;
struct TYPE_8__ {struct nvkm_memory* ramfc; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV03_PFIFO_CACHE1_GET ; 
 int /*<<< orphan*/  NV03_PFIFO_CACHE1_PUSH0 ; 
 int /*<<< orphan*/  NV03_PFIFO_CACHE1_PUSH1 ; 
 int /*<<< orphan*/  NV03_PFIFO_CACHE1_PUT ; 
 int /*<<< orphan*/  NV03_PFIFO_CACHES ; 
 int /*<<< orphan*/  NV04_PFIFO_CACHE1_DMA_PUSH ; 
 int /*<<< orphan*/  NV04_PFIFO_CACHE1_PULL0 ; 
 int /*<<< orphan*/  NV04_PFIFO_MODE ; 
 struct nv04_fifo_chan* nv04_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int nvkm_ro32 (struct nvkm_memory*,int) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_memory*,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
nv04_fifo_dma_fini(struct nvkm_fifo_chan *base)
{
	struct nv04_fifo_chan *chan = nv04_fifo_chan(base);
	struct nv04_fifo *fifo = chan->fifo;
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	struct nvkm_memory *fctx = device->imem->ramfc;
	const struct nv04_fifo_ramfc *c;
	unsigned long flags;
	u32 mask = fifo->base.nr - 1;
	u32 data = chan->ramfc;
	u32 chid;

	/* prevent fifo context switches */
	spin_lock_irqsave(&fifo->base.lock, flags);
	nvkm_wr32(device, NV03_PFIFO_CACHES, 0);

	/* if this channel is active, replace it with a null context */
	chid = nvkm_rd32(device, NV03_PFIFO_CACHE1_PUSH1) & mask;
	if (chid == chan->base.chid) {
		nvkm_mask(device, NV04_PFIFO_CACHE1_DMA_PUSH, 0x00000001, 0);
		nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0, 0);
		nvkm_mask(device, NV04_PFIFO_CACHE1_PULL0, 0x00000001, 0);

		c = fifo->ramfc;
		nvkm_kmap(fctx);
		do {
			u32 rm = ((1ULL << c->bits) - 1) << c->regs;
			u32 cm = ((1ULL << c->bits) - 1) << c->ctxs;
			u32 rv = (nvkm_rd32(device, c->regp) &  rm) >> c->regs;
			u32 cv = (nvkm_ro32(fctx, c->ctxp + data) & ~cm);
			nvkm_wo32(fctx, c->ctxp + data, cv | (rv << c->ctxs));
		} while ((++c)->bits);
		nvkm_done(fctx);

		c = fifo->ramfc;
		do {
			nvkm_wr32(device, c->regp, 0x00000000);
		} while ((++c)->bits);

		nvkm_wr32(device, NV03_PFIFO_CACHE1_GET, 0);
		nvkm_wr32(device, NV03_PFIFO_CACHE1_PUT, 0);
		nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH1, mask);
		nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0, 1);
		nvkm_wr32(device, NV04_PFIFO_CACHE1_PULL0, 1);
	}

	/* restore normal operation, after disabling dma mode */
	nvkm_mask(device, NV04_PFIFO_MODE, 1 << chan->base.chid, 0);
	nvkm_wr32(device, NV03_PFIFO_CACHES, 1);
	spin_unlock_irqrestore(&fifo->base.lock, flags);
}