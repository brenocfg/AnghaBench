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
struct nvkm_gr {TYPE_1__* func; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_2__ {int (* chan_new ) (struct nvkm_gr*,struct nvkm_fifo_chan*,struct nvkm_oclass const*,struct nvkm_object**) ;} ;

/* Variables and functions */
 struct nvkm_gr* nvkm_gr (int /*<<< orphan*/ ) ; 
 int stub1 (struct nvkm_gr*,struct nvkm_fifo_chan*,struct nvkm_oclass const*,struct nvkm_object**) ; 

__attribute__((used)) static int
nvkm_gr_cclass_new(struct nvkm_fifo_chan *chan,
		   const struct nvkm_oclass *oclass,
		   struct nvkm_object **pobject)
{
	struct nvkm_gr *gr = nvkm_gr(oclass->engine);
	if (gr->func->chan_new)
		return gr->func->chan_new(gr, chan, oclass, pobject);
	return 0;
}