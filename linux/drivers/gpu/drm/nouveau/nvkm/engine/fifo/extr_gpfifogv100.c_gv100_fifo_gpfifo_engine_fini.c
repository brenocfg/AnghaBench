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
struct nvkm_gpuobj {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_4__ {scalar_t__ index; } ;
struct nvkm_engine {TYPE_2__ subdev; } ;
struct TYPE_3__ {struct nvkm_gpuobj* inst; } ;
struct gk104_fifo_chan {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ NVKM_ENGINE_CE0 ; 
 scalar_t__ NVKM_ENGINE_CE_LAST ; 
 struct gk104_fifo_chan* gk104_fifo_chan (struct nvkm_fifo_chan*) ; 
 int gk104_fifo_gpfifo_kick (struct gk104_fifo_chan*) ; 
 int gv100_fifo_gpfifo_engine_valid (struct gk104_fifo_chan*,int,int) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_gpuobj*,int,int) ; 

int
gv100_fifo_gpfifo_engine_fini(struct nvkm_fifo_chan *base,
			      struct nvkm_engine *engine, bool suspend)
{
	struct gk104_fifo_chan *chan = gk104_fifo_chan(base);
	struct nvkm_gpuobj *inst = chan->base.inst;
	int ret;

	if (engine->subdev.index >= NVKM_ENGINE_CE0 &&
	    engine->subdev.index <= NVKM_ENGINE_CE_LAST)
		return gk104_fifo_gpfifo_kick(chan);

	ret = gv100_fifo_gpfifo_engine_valid(chan, false, false);
	if (ret && suspend)
		return ret;

	nvkm_kmap(inst);
	nvkm_wo32(inst, 0x0210, 0x00000000);
	nvkm_wo32(inst, 0x0214, 0x00000000);
	nvkm_done(inst);
	return ret;
}