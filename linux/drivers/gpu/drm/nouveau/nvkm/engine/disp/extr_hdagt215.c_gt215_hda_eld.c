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
typedef  int u8 ;
typedef  int u32 ;
struct nvkm_ior {int id; TYPE_3__* disp; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int const,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int const,int) ; 

void
gt215_hda_eld(struct nvkm_ior *ior, u8 *data, u8 size)
{
	struct nvkm_device *device = ior->disp->engine.subdev.device;
	const u32 soff = ior->id * 0x800;
	int i;

	for (i = 0; i < size; i++)
		nvkm_wr32(device, 0x61c440 + soff, (i << 8) | data[i]);
	for (; i < 0x60; i++)
		nvkm_wr32(device, 0x61c440 + soff, (i << 8));
	nvkm_mask(device, 0x61c448 + soff, 0x80000002, 0x80000002);
}