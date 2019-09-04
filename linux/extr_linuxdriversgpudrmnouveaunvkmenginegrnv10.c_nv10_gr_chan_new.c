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
struct nvkm_oclass {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_gr {int dummy; } ;
struct nvkm_fifo_chan {int chid; } ;
struct nvkm_device {scalar_t__ card_type; int chipset; } ;
struct nv10_gr_chan {int chid; struct nvkm_object object; struct nv10_gr* gr; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv10_gr {int /*<<< orphan*/  lock; struct nv10_gr_chan** chan; TYPE_3__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NV03_PGRAPH_XY_LOGIC_MISC0 ; 
 int NV10_PGRAPH_CTX_USER ; 
 int NV10_PGRAPH_DEBUG_4 ; 
 int /*<<< orphan*/  NV17_WRITE_CTX (int,int) ; 
 scalar_t__ NV_11 ; 
 int /*<<< orphan*/  NV_WRITE_CTX (int,int) ; 
 struct nv10_gr_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nv10_gr* nv10_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nv10_gr_chan ; 
 int /*<<< orphan*/  nv10_gr_create_pipe (struct nv10_gr_chan*) ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_object*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
nv10_gr_chan_new(struct nvkm_gr *base, struct nvkm_fifo_chan *fifoch,
		 const struct nvkm_oclass *oclass, struct nvkm_object **pobject)
{
	struct nv10_gr *gr = nv10_gr(base);
	struct nv10_gr_chan *chan;
	struct nvkm_device *device = gr->base.engine.subdev.device;
	unsigned long flags;

	if (!(chan = kzalloc(sizeof(*chan), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_object_ctor(&nv10_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fifoch->chid;
	*pobject = &chan->object;

	NV_WRITE_CTX(0x00400e88, 0x08000000);
	NV_WRITE_CTX(0x00400e9c, 0x4b7fffff);
	NV_WRITE_CTX(NV03_PGRAPH_XY_LOGIC_MISC0, 0x0001ffff);
	NV_WRITE_CTX(0x00400e10, 0x00001000);
	NV_WRITE_CTX(0x00400e14, 0x00001000);
	NV_WRITE_CTX(0x00400e30, 0x00080008);
	NV_WRITE_CTX(0x00400e34, 0x00080008);
	if (device->card_type >= NV_11 && device->chipset >= 0x17) {
		/* is it really needed ??? */
		NV17_WRITE_CTX(NV10_PGRAPH_DEBUG_4,
			       nvkm_rd32(device, NV10_PGRAPH_DEBUG_4));
		NV17_WRITE_CTX(0x004006b0, nvkm_rd32(device, 0x004006b0));
		NV17_WRITE_CTX(0x00400eac, 0x0fff0000);
		NV17_WRITE_CTX(0x00400eb0, 0x0fff0000);
		NV17_WRITE_CTX(0x00400ec0, 0x00000080);
		NV17_WRITE_CTX(0x00400ed0, 0x00000080);
	}
	NV_WRITE_CTX(NV10_PGRAPH_CTX_USER, chan->chid << 24);

	nv10_gr_create_pipe(chan);

	spin_lock_irqsave(&gr->lock, flags);
	gr->chan[chan->chid] = chan;
	spin_unlock_irqrestore(&gr->lock, flags);
	return 0;
}