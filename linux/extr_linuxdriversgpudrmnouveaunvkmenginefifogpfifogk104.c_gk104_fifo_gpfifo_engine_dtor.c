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
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_6__ {size_t index; } ;
struct nvkm_engine {TYPE_3__ subdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vmm; } ;
struct gk104_fifo_chan {TYPE_2__* engn; TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  inst; int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 struct gk104_fifo_chan* gk104_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  nvkm_gpuobj_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_vmm_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
gk104_fifo_gpfifo_engine_dtor(struct nvkm_fifo_chan *base,
			      struct nvkm_engine *engine)
{
	struct gk104_fifo_chan *chan = gk104_fifo_chan(base);
	nvkm_vmm_put(chan->base.vmm, &chan->engn[engine->subdev.index].vma);
	nvkm_gpuobj_del(&chan->engn[engine->subdev.index].inst);
}