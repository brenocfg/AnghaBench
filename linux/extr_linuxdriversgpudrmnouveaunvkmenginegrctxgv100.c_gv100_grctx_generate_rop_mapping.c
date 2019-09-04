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
typedef  int u8 ;
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gf100_gr {int tpc_total; int screen_tile_row_offset; int* tile; TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gv100_grctx_generate_rop_mapping(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	u32 data;
	int i, j;

	/* Pack tile map into register format. */
	nvkm_wr32(device, 0x418bb8, (gr->tpc_total << 8) |
				     gr->screen_tile_row_offset);
	for (i = 0; i < 11; i++) {
		for (data = 0, j = 0; j < 6; j++)
			data |= (gr->tile[i * 6 + j] & 0x1f) << (j * 5);
		nvkm_wr32(device, 0x418b08 + (i * 4), data);
		nvkm_wr32(device, 0x41bf00 + (i * 4), data);
		nvkm_wr32(device, 0x40780c + (i * 4), data);
	}

	/* GPC_BROADCAST.TP_BROADCAST */
	nvkm_wr32(device, 0x41bfd0, (gr->tpc_total << 8) |
				     gr->screen_tile_row_offset);
	for (i = 0, j = 1; i < 5; i++, j += 4) {
		u8 v19 = (1 << (j + 0)) % gr->tpc_total;
		u8 v20 = (1 << (j + 1)) % gr->tpc_total;
		u8 v21 = (1 << (j + 2)) % gr->tpc_total;
		u8 v22 = (1 << (j + 3)) % gr->tpc_total;
		nvkm_wr32(device, 0x41bfb0 + (i * 4), (v22 << 24) |
						      (v21 << 16) |
						      (v20 <<  8) |
						       v19);
	}

	/* UNK78xx */
	nvkm_wr32(device, 0x4078bc, (gr->tpc_total << 8) |
				     gr->screen_tile_row_offset);
}