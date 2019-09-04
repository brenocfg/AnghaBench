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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
gk20a_ibus_init_ibus_ring(struct nvkm_subdev *ibus)
{
	struct nvkm_device *device = ibus->device;
	nvkm_mask(device, 0x137250, 0x3f, 0);

	nvkm_mask(device, 0x000200, 0x20, 0);
	udelay(20);
	nvkm_mask(device, 0x000200, 0x20, 0x20);

	nvkm_wr32(device, 0x12004c, 0x4);
	nvkm_wr32(device, 0x122204, 0x2);
	nvkm_rd32(device, 0x122204);

	/*
	 * Bug: increase clock timeout to avoid operation failure at high
	 * gpcclk rate.
	 */
	nvkm_wr32(device, 0x122354, 0x800);
	nvkm_wr32(device, 0x128328, 0x800);
	nvkm_wr32(device, 0x124320, 0x800);
}