#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gf100_gr {TYPE_2__ base; } ;

/* Variables and functions */
 int EAGAIN ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

int
gf100_gr_wait_idle(struct gf100_gr *gr)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	unsigned long end_jiffies = jiffies + msecs_to_jiffies(2000);
	bool gr_enabled, ctxsw_active, gr_busy;

	do {
		/*
		 * required to make sure FIFO_ENGINE_STATUS (0x2640) is
		 * up-to-date
		 */
		nvkm_rd32(device, 0x400700);

		gr_enabled = nvkm_rd32(device, 0x200) & 0x1000;
		ctxsw_active = nvkm_rd32(device, 0x2640) & 0x8000;
		gr_busy = nvkm_rd32(device, 0x40060c) & 0x1;

		if (!gr_enabled || (!gr_busy && !ctxsw_active))
			return 0;
	} while (time_before(jiffies, end_jiffies));

	nvkm_error(subdev,
		   "wait for idle timeout (en: %d, ctxsw: %d, busy: %d)\n",
		   gr_enabled, ctxsw_active, gr_busy);
	return -EAGAIN;
}