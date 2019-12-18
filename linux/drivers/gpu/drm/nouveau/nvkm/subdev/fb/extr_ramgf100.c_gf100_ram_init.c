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
struct nvkm_ram {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_6__ {int type; TYPE_2__* fb; } ;
struct gf100_ram {TYPE_3__ base; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;

/* Variables and functions */
#define  NVKM_RAM_TYPE_GDDR5 128 
 struct gf100_ram* gf100_ram (struct nvkm_ram*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int const) ; 

int
gf100_ram_init(struct nvkm_ram *base)
{
	static const u8  train0[] = {
		0x00, 0xff, 0x55, 0xaa, 0x33, 0xcc,
		0x00, 0xff, 0xff, 0x00, 0xff, 0x00,
	};
	static const u32 train1[] = {
		0x00000000, 0xffffffff,
		0x55555555, 0xaaaaaaaa,
		0x33333333, 0xcccccccc,
		0xf0f0f0f0, 0x0f0f0f0f,
		0x00ff00ff, 0xff00ff00,
		0x0000ffff, 0xffff0000,
	};
	struct gf100_ram *ram = gf100_ram(base);
	struct nvkm_device *device = ram->base.fb->subdev.device;
	int i;

	switch (ram->base.type) {
	case NVKM_RAM_TYPE_GDDR5:
		break;
	default:
		return 0;
	}

	/* prepare for ddr link training, and load training patterns */
	for (i = 0; i < 0x30; i++) {
		nvkm_wr32(device, 0x10f968, 0x00000000 | (i << 8));
		nvkm_wr32(device, 0x10f96c, 0x00000000 | (i << 8));
		nvkm_wr32(device, 0x10f920, 0x00000100 | train0[i % 12]);
		nvkm_wr32(device, 0x10f924, 0x00000100 | train0[i % 12]);
		nvkm_wr32(device, 0x10f918,              train1[i % 12]);
		nvkm_wr32(device, 0x10f91c,              train1[i % 12]);
		nvkm_wr32(device, 0x10f920, 0x00000000 | train0[i % 12]);
		nvkm_wr32(device, 0x10f924, 0x00000000 | train0[i % 12]);
		nvkm_wr32(device, 0x10f918,              train1[i % 12]);
		nvkm_wr32(device, 0x10f91c,              train1[i % 12]);
	}

	return 0;
}