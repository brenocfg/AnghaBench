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
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_2__ {size_t index; } ;
struct nvkm_engine {TYPE_1__ subdev; } ;
struct nv50_fifo_chan {int /*<<< orphan*/ * engn; } ;

/* Variables and functions */
 struct nv50_fifo_chan* nv50_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  nvkm_gpuobj_del (int /*<<< orphan*/ *) ; 

void
nv50_fifo_chan_engine_dtor(struct nvkm_fifo_chan *base,
			   struct nvkm_engine *engine)
{
	struct nv50_fifo_chan *chan = nv50_fifo_chan(base);
	nvkm_gpuobj_del(&chan->engn[engine->subdev.index]);
}