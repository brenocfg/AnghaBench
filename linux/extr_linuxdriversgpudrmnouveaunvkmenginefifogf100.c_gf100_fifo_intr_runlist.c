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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  wait; } ;
struct TYPE_4__ {struct nvkm_subdev subdev; } ;
struct TYPE_5__ {TYPE_1__ engine; } ;
struct gf100_fifo {TYPE_3__ runlist; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gf100_fifo_intr_runlist(struct gf100_fifo *fifo)
{
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 intr = nvkm_rd32(device, 0x002a00);

	if (intr & 0x10000000) {
		wake_up(&fifo->runlist.wait);
		nvkm_wr32(device, 0x002a00, 0x10000000);
		intr &= ~0x10000000;
	}

	if (intr) {
		nvkm_error(subdev, "RUNLIST %08x\n", intr);
		nvkm_wr32(device, 0x002a00, intr);
	}
}