#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_4__ subdev; } ;
struct TYPE_6__ {TYPE_1__ engine; } ;
struct gf100_gr {int sm_nr; TYPE_3__* sm; TYPE_2__ base; } ;
struct TYPE_7__ {int gpc; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int const,int) ; 
 int const nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
gf100_grctx_generate_r4060a8(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	const u8 gpcmax = nvkm_rd32(device, 0x022430);
	const u8 tpcmax = nvkm_rd32(device, 0x022434) * gpcmax;
	int i, j, sm = 0;
	u32 data;

	for (i = 0; i < DIV_ROUND_UP(tpcmax, 4); i++) {
		for (data = 0, j = 0; j < 4; j++) {
			if (sm < gr->sm_nr)
				data |= gr->sm[sm++].gpc << (j * 8);
			else
				data |= 0x1f << (j * 8);
		}
		nvkm_wr32(device, 0x4060a8 + (i * 4), data);
	}
}