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
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gf100_gr {int gpc_nr; int* ppc_nr; int* ppc_mask; TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_UNIT (int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

void
gk104_gr_init_ppc_exceptions(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	int gpc, ppc;

	for (gpc = 0; gpc < gr->gpc_nr; gpc++) {
		for (ppc = 0; ppc < gr->ppc_nr[gpc]; ppc++) {
			if (!(gr->ppc_mask[gpc] & (1 << ppc)))
				continue;
			nvkm_wr32(device, PPC_UNIT(gpc, ppc, 0x038), 0xc0000000);
		}
	}
}