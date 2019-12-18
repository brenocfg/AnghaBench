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
struct nvkm_sec2 {scalar_t__ addr; int /*<<< orphan*/  work; } ;
struct nvkm_engine {struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,scalar_t__) ; 
 struct nvkm_sec2* nvkm_sec2 (struct nvkm_engine*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvkm_sec2_intr(struct nvkm_engine *engine)
{
	struct nvkm_sec2 *sec2 = nvkm_sec2(engine);
	struct nvkm_subdev *subdev = &engine->subdev;
	struct nvkm_device *device = subdev->device;
	u32 disp = nvkm_rd32(device, sec2->addr + 0x01c);
	u32 intr = nvkm_rd32(device, sec2->addr + 0x008) & disp & ~(disp >> 16);

	if (intr & 0x00000040) {
		schedule_work(&sec2->work);
		nvkm_wr32(device, sec2->addr + 0x004, 0x00000040);
		intr &= ~0x00000040;
	}

	if (intr) {
		nvkm_error(subdev, "unhandled intr %08x\n", intr);
		nvkm_wr32(device, sec2->addr + 0x004, intr);

	}
}