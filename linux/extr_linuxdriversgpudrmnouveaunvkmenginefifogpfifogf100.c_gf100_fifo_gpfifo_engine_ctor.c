#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvkm_object {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_6__ {int index; } ;
struct nvkm_engine {TYPE_1__ subdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  vmm; } ;
struct gf100_fifo_chan {TYPE_3__* engn; TYPE_2__ base; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; } ;
struct TYPE_8__ {int /*<<< orphan*/  vma; TYPE_4__* inst; } ;

/* Variables and functions */
 struct gf100_fifo_chan* gf100_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  gf100_fifo_gpfifo_engine_addr (struct nvkm_engine*) ; 
 int nvkm_memory_map (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nvkm_object_bind (struct nvkm_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int nvkm_vmm_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gf100_fifo_gpfifo_engine_ctor(struct nvkm_fifo_chan *base,
			      struct nvkm_engine *engine,
			      struct nvkm_object *object)
{
	struct gf100_fifo_chan *chan = gf100_fifo_chan(base);
	int engn = engine->subdev.index;
	int ret;

	if (!gf100_fifo_gpfifo_engine_addr(engine))
		return 0;

	ret = nvkm_object_bind(object, NULL, 0, &chan->engn[engn].inst);
	if (ret)
		return ret;

	ret = nvkm_vmm_get(chan->base.vmm, 12, chan->engn[engn].inst->size,
			   &chan->engn[engn].vma);
	if (ret)
		return ret;

	return nvkm_memory_map(chan->engn[engn].inst, 0, chan->base.vmm,
			       chan->engn[engn].vma, NULL, 0);
}