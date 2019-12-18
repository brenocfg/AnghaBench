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
struct nvkm_subdev {int index; struct nvkm_device* device; } ;
struct nvkm_engine {struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int NVKM_ENGINE_CE0 ; 
 int /*<<< orphan*/  gp100_ce_intr_launcherr (struct nvkm_engine*,int const) ; 
 int nvkm_rd32 (struct nvkm_device*,int const) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,...) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int const,int) ; 

void
gp100_ce_intr(struct nvkm_engine *ce)
{
	const u32 base = (ce->subdev.index - NVKM_ENGINE_CE0) * 0x80;
	struct nvkm_subdev *subdev = &ce->subdev;
	struct nvkm_device *device = subdev->device;
	u32 mask = nvkm_rd32(device, 0x10440c + base);
	u32 intr = nvkm_rd32(device, 0x104410 + base) & mask;
	if (intr & 0x00000001) { //XXX: guess
		nvkm_warn(subdev, "BLOCKPIPE\n");
		nvkm_wr32(device, 0x104410 + base, 0x00000001);
		intr &= ~0x00000001;
	}
	if (intr & 0x00000002) { //XXX: guess
		nvkm_warn(subdev, "NONBLOCKPIPE\n");
		nvkm_wr32(device, 0x104410 + base, 0x00000002);
		intr &= ~0x00000002;
	}
	if (intr & 0x00000004) {
		gp100_ce_intr_launcherr(ce, base);
		nvkm_wr32(device, 0x104410 + base, 0x00000004);
		intr &= ~0x00000004;
	}
	if (intr) {
		nvkm_warn(subdev, "intr %08x\n", intr);
		nvkm_wr32(device, 0x104410 + base, intr);
	}
}