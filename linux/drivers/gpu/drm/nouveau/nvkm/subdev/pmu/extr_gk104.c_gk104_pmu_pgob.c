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
struct nvkm_pmu {TYPE_1__ subdev; } ;
struct nvkm_device {int chipset; int /*<<< orphan*/  cfgopt; int /*<<< orphan*/  fuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  magic (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ nvkm_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int nvkm_fuse_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static void
gk104_pmu_pgob(struct nvkm_pmu *pmu, bool enable)
{
	struct nvkm_device *device = pmu->subdev.device;

	if (!(nvkm_fuse_read(device->fuse, 0x31c) & 0x00000001))
		return;

	nvkm_mask(device, 0x000200, 0x00001000, 0x00000000);
	nvkm_rd32(device, 0x000200);
	nvkm_mask(device, 0x000200, 0x08000000, 0x08000000);
	msleep(50);

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000002);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x020004, 0xc0000000, enable ? 0xc0000000 : 0x40000000);
	msleep(50);

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000000);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x000200, 0x08000000, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00001000, 0x00001000);
	nvkm_rd32(device, 0x000200);

	if (nvkm_boolopt(device->cfgopt, "War00C800_0", true)) {
		switch (device->chipset) {
		case 0xe4:
			magic(device, 0x04000000);
			magic(device, 0x06000000);
			magic(device, 0x0c000000);
			magic(device, 0x0e000000);
			break;
		case 0xe6:
			magic(device, 0x02000000);
			magic(device, 0x04000000);
			magic(device, 0x0a000000);
			break;
		case 0xe7:
			magic(device, 0x02000000);
			break;
		default:
			break;
		}
	}
}