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
struct nvkm_oclass {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nv50_disp_chan_mthd {int dummy; } ;
struct nv50_disp_chan_func {int dummy; } ;
struct TYPE_2__ {int ctrl; int user; } ;
struct nv50_disp_chan {int head; TYPE_1__ chid; struct nv50_disp* disp; struct nv50_disp_chan_mthd const* mthd; struct nv50_disp_chan_func const* func; struct nvkm_object object; } ;
struct nv50_disp {struct nv50_disp_chan** chan; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv50_disp_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_disp_chan ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_object*) ; 

int
nv50_disp_chan_new_(const struct nv50_disp_chan_func *func,
		    const struct nv50_disp_chan_mthd *mthd,
		    struct nv50_disp *disp, int ctrl, int user, int head,
		    const struct nvkm_oclass *oclass,
		    struct nvkm_object **pobject)
{
	struct nv50_disp_chan *chan;

	if (!(chan = kzalloc(sizeof(*chan), GFP_KERNEL)))
		return -ENOMEM;
	*pobject = &chan->object;

	nvkm_object_ctor(&nv50_disp_chan, oclass, &chan->object);
	chan->func = func;
	chan->mthd = mthd;
	chan->disp = disp;
	chan->chid.ctrl = ctrl;
	chan->chid.user = user;
	chan->head = head;

	if (disp->chan[chan->chid.user]) {
		chan->chid.user = -1;
		return -EBUSY;
	}
	disp->chan[chan->chid.user] = chan;
	return 0;
}