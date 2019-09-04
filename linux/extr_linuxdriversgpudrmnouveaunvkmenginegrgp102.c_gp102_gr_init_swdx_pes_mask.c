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
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gf100_gr {int gpc_nr; TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPC_UNIT (int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
gp102_gr_init_swdx_pes_mask(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	u32 mask = 0, data, gpc;

	for (gpc = 0; gpc < gr->gpc_nr; gpc++) {
		data = nvkm_rd32(device, GPC_UNIT(gpc, 0x0c50)) & 0x0000000f;
		mask |= data << (gpc * 4);
	}

	nvkm_wr32(device, 0x4181d0, mask);
}