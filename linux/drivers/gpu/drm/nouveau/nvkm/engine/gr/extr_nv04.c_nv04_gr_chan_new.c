#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvkm_oclass {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_gr {int dummy; } ;
struct nvkm_fifo_chan {size_t chid; } ;
struct nv04_gr_chan {size_t chid; struct nvkm_object object; struct nv04_gr* gr; } ;
struct nv04_gr {int /*<<< orphan*/  lock; struct nv04_gr_chan** chan; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_3 ; 
 int* ctx_reg (struct nv04_gr_chan*,int /*<<< orphan*/ ) ; 
 struct nv04_gr_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nv04_gr* nv04_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nv04_gr_chan ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
nv04_gr_chan_new(struct nvkm_gr *base, struct nvkm_fifo_chan *fifoch,
		 const struct nvkm_oclass *oclass, struct nvkm_object **pobject)
{
	struct nv04_gr *gr = nv04_gr(base);
	struct nv04_gr_chan *chan;
	unsigned long flags;

	if (!(chan = kzalloc(sizeof(*chan), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_object_ctor(&nv04_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fifoch->chid;
	*pobject = &chan->object;

	*ctx_reg(chan, NV04_PGRAPH_DEBUG_3) = 0xfad4ff31;

	spin_lock_irqsave(&gr->lock, flags);
	gr->chan[chan->chid] = chan;
	spin_unlock_irqrestore(&gr->lock, flags);
	return 0;
}