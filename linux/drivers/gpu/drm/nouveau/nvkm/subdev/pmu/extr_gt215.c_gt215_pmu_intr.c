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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct nvkm_pmu {TYPE_1__ recv; struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,...) ; 
 int /*<<< orphan*/  nvkm_info (struct nvkm_subdev*,char*,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void
gt215_pmu_intr(struct nvkm_pmu *pmu)
{
	struct nvkm_subdev *subdev = &pmu->subdev;
	struct nvkm_device *device = subdev->device;
	u32 disp = nvkm_rd32(device, 0x10a01c);
	u32 intr = nvkm_rd32(device, 0x10a008) & disp & ~(disp >> 16);

	if (intr & 0x00000020) {
		u32 stat = nvkm_rd32(device, 0x10a16c);
		if (stat & 0x80000000) {
			nvkm_error(subdev, "UAS fault at %06x addr %08x\n",
				   stat & 0x00ffffff,
				   nvkm_rd32(device, 0x10a168));
			nvkm_wr32(device, 0x10a16c, 0x00000000);
			intr &= ~0x00000020;
		}
	}

	if (intr & 0x00000040) {
		schedule_work(&pmu->recv.work);
		nvkm_wr32(device, 0x10a004, 0x00000040);
		intr &= ~0x00000040;
	}

	if (intr & 0x00000080) {
		nvkm_info(subdev, "wr32 %06x %08x\n",
			  nvkm_rd32(device, 0x10a7a0),
			  nvkm_rd32(device, 0x10a7a4));
		nvkm_wr32(device, 0x10a004, 0x00000080);
		intr &= ~0x00000080;
	}

	if (intr) {
		nvkm_error(subdev, "intr %08x\n", intr);
		nvkm_wr32(device, 0x10a004, intr);
	}
}