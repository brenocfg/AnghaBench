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
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_fb {TYPE_1__ subdev; } ;
struct nvkm_device {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_ref (struct nvkm_fb*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int /*<<< orphan*/ ) ; 

void
nv30_fb_init(struct nvkm_fb *fb)
{
	struct nvkm_device *device = fb->subdev.device;
	int i, j;

	/* Init the memory timing regs at 0x10037c/0x1003ac */
	if (device->chipset == 0x30 ||
	    device->chipset == 0x31 ||
	    device->chipset == 0x35) {
		/* Related to ROP count */
		int n = (device->chipset == 0x31 ? 2 : 4);
		int l = nvkm_rd32(device, 0x1003d0);

		for (i = 0; i < n; i++) {
			for (j = 0; j < 3; j++)
				nvkm_wr32(device, 0x10037c + 0xc * i + 0x4 * j,
					  calc_ref(fb, l, 0, j));

			for (j = 0; j < 2; j++)
				nvkm_wr32(device, 0x1003ac + 0x8 * i + 0x4 * j,
					  calc_ref(fb, l, 1, j));
		}
	}
}