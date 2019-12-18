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
struct nvkm_device {int dummy; } ;
struct nv10_gr_chan {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv10_gr {struct nv10_gr_chan** chan; TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PGRAPH_TRAPPED_ADDR ; 
 int /*<<< orphan*/  nv04_gr_idle (TYPE_3__*) ; 
 struct nv10_gr_chan* nv10_gr_channel (struct nv10_gr*) ; 
 int /*<<< orphan*/  nv10_gr_load_context (struct nv10_gr_chan*,int) ; 
 int /*<<< orphan*/  nv10_gr_unload_context (struct nv10_gr_chan*) ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv10_gr_context_switch(struct nv10_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	struct nv10_gr_chan *prev = NULL;
	struct nv10_gr_chan *next = NULL;
	int chid;

	nv04_gr_idle(&gr->base);

	/* If previous context is valid, we need to save it */
	prev = nv10_gr_channel(gr);
	if (prev)
		nv10_gr_unload_context(prev);

	/* load context for next channel */
	chid = (nvkm_rd32(device, NV04_PGRAPH_TRAPPED_ADDR) >> 20) & 0x1f;
	next = gr->chan[chid];
	if (next)
		nv10_gr_load_context(next, chid);
}