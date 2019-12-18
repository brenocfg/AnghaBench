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
struct nvkm_therm {int /*<<< orphan*/  subdev; } ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {struct nvkm_therm* therm; } ;
struct nvkm_bus {struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,...) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_subdev_intr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
nv50_bus_intr(struct nvkm_bus *bus)
{
	struct nvkm_subdev *subdev = &bus->subdev;
	struct nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x001100) & nvkm_rd32(device, 0x001140);

	if (stat & 0x00000008) {
		u32 addr = nvkm_rd32(device, 0x009084);
		u32 data = nvkm_rd32(device, 0x009088);

		nvkm_error(subdev, "MMIO %s of %08x FAULT at %06x\n",
			   (addr & 0x00000002) ? "write" : "read", data,
			   (addr & 0x00fffffc));

		stat &= ~0x00000008;
		nvkm_wr32(device, 0x001100, 0x00000008);
	}

	if (stat & 0x00010000) {
		struct nvkm_therm *therm = device->therm;
		if (therm)
			nvkm_subdev_intr(&therm->subdev);
		stat &= ~0x00010000;
		nvkm_wr32(device, 0x001100, 0x00010000);
	}

	if (stat) {
		nvkm_error(subdev, "intr %08x\n", stat);
		nvkm_mask(device, 0x001140, stat, 0);
	}
}