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
struct nvkm_ior {int id; TYPE_3__* disp; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int const,int,int) ; 

void
gf119_hda_hpd(struct nvkm_ior *ior, int head, bool present)
{
	struct nvkm_device *device = ior->disp->engine.subdev.device;
	const u32 hoff = 0x800 * head;
	u32 data = 0x80000000;
	u32 mask = 0x80000001;
	if (present) {
		nvkm_mask(device, 0x616548 + hoff, 0x00000070, 0x00000000);
		data |= 0x00000001;
	} else {
		mask |= 0x00000002;
	}
	nvkm_mask(device, 0x10ec10 + ior->id * 0x030, mask, data);
}