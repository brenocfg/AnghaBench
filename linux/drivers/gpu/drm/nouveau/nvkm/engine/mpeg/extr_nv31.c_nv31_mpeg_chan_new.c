#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvkm_oclass {int /*<<< orphan*/  engine; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct nv31_mpeg_chan {struct nvkm_object object; struct nvkm_fifo_chan* fifo; struct nv31_mpeg* mpeg; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct nv31_mpeg {TYPE_1__ engine; struct nv31_mpeg_chan* chan; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv31_mpeg_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nv31_mpeg* nv31_mpeg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv31_mpeg_chan ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
nv31_mpeg_chan_new(struct nvkm_fifo_chan *fifoch,
		   const struct nvkm_oclass *oclass,
		   struct nvkm_object **pobject)
{
	struct nv31_mpeg *mpeg = nv31_mpeg(oclass->engine);
	struct nv31_mpeg_chan *chan;
	unsigned long flags;
	int ret = -EBUSY;

	if (!(chan = kzalloc(sizeof(*chan), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_object_ctor(&nv31_mpeg_chan, oclass, &chan->object);
	chan->mpeg = mpeg;
	chan->fifo = fifoch;
	*pobject = &chan->object;

	spin_lock_irqsave(&mpeg->engine.lock, flags);
	if (!mpeg->chan) {
		mpeg->chan = chan;
		ret = 0;
	}
	spin_unlock_irqrestore(&mpeg->engine.lock, flags);
	return ret;
}