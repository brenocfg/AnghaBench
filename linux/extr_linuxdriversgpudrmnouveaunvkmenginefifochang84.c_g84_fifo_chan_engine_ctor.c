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
struct nvkm_object {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_2__ {int index; } ;
struct nvkm_engine {TYPE_1__ subdev; } ;
struct nv50_fifo_chan {int /*<<< orphan*/ * engn; } ;

/* Variables and functions */
 scalar_t__ g84_fifo_chan_engine_addr (struct nvkm_engine*) ; 
 struct nv50_fifo_chan* nv50_fifo_chan (struct nvkm_fifo_chan*) ; 
 int nvkm_object_bind (struct nvkm_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g84_fifo_chan_engine_ctor(struct nvkm_fifo_chan *base,
			  struct nvkm_engine *engine,
			  struct nvkm_object *object)
{
	struct nv50_fifo_chan *chan = nv50_fifo_chan(base);
	int engn = engine->subdev.index;

	if (g84_fifo_chan_engine_addr(engine) < 0)
		return 0;

	return nvkm_object_bind(object, NULL, 0, &chan->engn[engn]);
}