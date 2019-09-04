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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct nvkm_disp {TYPE_1__ engine; } ;
struct nvkm_device {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_disp_vblank (struct nvkm_disp*,int) ; 
 int /*<<< orphan*/  nvkm_info (struct nvkm_subdev*,char*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv04_disp_intr(struct nvkm_disp *disp)
{
	struct nvkm_subdev *subdev = &disp->engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 crtc0 = nvkm_rd32(device, 0x600100);
	u32 crtc1 = nvkm_rd32(device, 0x602100);
	u32 pvideo;

	if (crtc0 & 0x00000001) {
		nvkm_disp_vblank(disp, 0);
		nvkm_wr32(device, 0x600100, 0x00000001);
	}

	if (crtc1 & 0x00000001) {
		nvkm_disp_vblank(disp, 1);
		nvkm_wr32(device, 0x602100, 0x00000001);
	}

	if (device->chipset >= 0x10 && device->chipset <= 0x40) {
		pvideo = nvkm_rd32(device, 0x8100);
		if (pvideo & ~0x11)
			nvkm_info(subdev, "PVIDEO intr: %08x\n", pvideo);
		nvkm_wr32(device, 0x8100, pvideo);
	}
}