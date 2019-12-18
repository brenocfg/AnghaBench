#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_hwsq {struct nvkm_subdev* subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,...) ; 
 int /*<<< orphan*/  nvkm_hwsq_wait (struct nvkm_hwsq*,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

void
nvkm_hwsq_wait_vblank(struct nvkm_hwsq *hwsq)
{
	struct nvkm_subdev *subdev = hwsq->subdev;
	struct nvkm_device *device = subdev->device;
	u32 heads, x, y, px = 0;
	int i, head_sync;

	heads = nvkm_rd32(device, 0x610050);
	for (i = 0; i < 2; i++) {
		/* Heuristic: sync to head with biggest resolution */
		if (heads & (2 << (i << 3))) {
			x = nvkm_rd32(device, 0x610b40 + (0x540 * i));
			y = (x & 0xffff0000) >> 16;
			x &= 0x0000ffff;
			if ((x * y) > px) {
				px = (x * y);
				head_sync = i;
			}
		}
	}

	if (px == 0) {
		nvkm_debug(subdev, "WAIT VBLANK !NO ACTIVE HEAD\n");
		return;
	}

	nvkm_debug(subdev, "WAIT VBLANK HEAD%d\n", head_sync);
	nvkm_hwsq_wait(hwsq, head_sync ? 0x3 : 0x1, 0x0);
	nvkm_hwsq_wait(hwsq, head_sync ? 0x3 : 0x1, 0x1);
}