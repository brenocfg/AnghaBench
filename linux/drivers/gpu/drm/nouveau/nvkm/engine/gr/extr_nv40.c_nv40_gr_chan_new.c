#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_oclass {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_gr {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct nv40_gr_chan {struct nv40_gr* gr; int /*<<< orphan*/  head; struct nvkm_object object; struct nvkm_fifo_chan* fifo; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct nv40_gr {TYPE_2__ base; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv40_gr_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nv40_gr* nv40_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nv40_gr_chan ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
nv40_gr_chan_new(struct nvkm_gr *base, struct nvkm_fifo_chan *fifoch,
		 const struct nvkm_oclass *oclass, struct nvkm_object **pobject)
{
	struct nv40_gr *gr = nv40_gr(base);
	struct nv40_gr_chan *chan;
	unsigned long flags;

	if (!(chan = kzalloc(sizeof(*chan), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_object_ctor(&nv40_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->fifo = fifoch;
	*pobject = &chan->object;

	spin_lock_irqsave(&chan->gr->base.engine.lock, flags);
	list_add(&chan->head, &gr->chan);
	spin_unlock_irqrestore(&chan->gr->base.engine.lock, flags);
	return 0;
}