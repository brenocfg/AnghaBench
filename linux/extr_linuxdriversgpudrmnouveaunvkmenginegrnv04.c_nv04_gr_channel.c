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
struct nv04_gr_chan {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv04_gr {struct nv04_gr_chan** chan; TYPE_3__ base; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nv04_gr_chan**) ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_CONTROL ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_USER ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nv04_gr_chan *
nv04_gr_channel(struct nv04_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	struct nv04_gr_chan *chan = NULL;
	if (nvkm_rd32(device, NV04_PGRAPH_CTX_CONTROL) & 0x00010000) {
		int chid = nvkm_rd32(device, NV04_PGRAPH_CTX_USER) >> 24;
		if (chid < ARRAY_SIZE(gr->chan))
			chan = gr->chan[chid];
	}
	return chan;
}