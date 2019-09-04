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
struct ramfuc_reg {int addr; int data; } ;
struct ramfuc {int /*<<< orphan*/  memx; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct nvkm_fb {TYPE_3__ subdev; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_5__ {struct ramfuc base; } ;
struct TYPE_4__ {struct nvkm_fb* fb; } ;
struct gk104_ram {int pnuts; TYPE_2__ fuc; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_memx_wr32 (int /*<<< orphan*/ ,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static void
gk104_ram_nuts(struct gk104_ram *ram, struct ramfuc_reg *reg,
	       u32 _mask, u32 _data, u32 _copy)
{
	struct nvkm_fb *fb = ram->base.fb;
	struct ramfuc *fuc = &ram->fuc.base;
	struct nvkm_device *device = fb->subdev.device;
	u32 addr = 0x110000 + (reg->addr & 0xfff);
	u32 mask = _mask | _copy;
	u32 data = (_data & _mask) | (reg->data & _copy);
	u32 i;

	for (i = 0; i < 16; i++, addr += 0x1000) {
		if (ram->pnuts & (1 << i)) {
			u32 prev = nvkm_rd32(device, addr);
			u32 next = (prev & ~mask) | data;
			nvkm_memx_wr32(fuc->memx, addr, next);
		}
	}
}