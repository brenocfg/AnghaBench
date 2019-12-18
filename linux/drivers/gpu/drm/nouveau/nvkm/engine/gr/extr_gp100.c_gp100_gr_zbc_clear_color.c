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
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct gf100_gr {TYPE_4__* zbc_color; TYPE_3__ base; } ;
struct TYPE_8__ {int format; int /*<<< orphan*/ * ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int const) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int const,int /*<<< orphan*/ ) ; 

void
gp100_gr_zbc_clear_color(struct gf100_gr *gr, int zbc)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	const int znum =  zbc - 1;
	const u32 zoff = znum * 4;

	if (gr->zbc_color[zbc].format) {
		nvkm_wr32(device, 0x418010 + zoff, gr->zbc_color[zbc].ds[0]);
		nvkm_wr32(device, 0x41804c + zoff, gr->zbc_color[zbc].ds[1]);
		nvkm_wr32(device, 0x418088 + zoff, gr->zbc_color[zbc].ds[2]);
		nvkm_wr32(device, 0x4180c4 + zoff, gr->zbc_color[zbc].ds[3]);
	}

	nvkm_mask(device, 0x418100 + ((znum / 4) * 4),
			  0x0000007f << ((znum % 4) * 7),
			  gr->zbc_color[zbc].format << ((znum % 4) * 7));
}