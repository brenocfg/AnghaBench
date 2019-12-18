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
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_i2c {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
gk104_aux_mask(struct nvkm_i2c *i2c, u32 type, u32 mask, u32 data)
{
	struct nvkm_device *device = i2c->subdev.device;
	u32 temp = nvkm_rd32(device, 0x00dc68), i;
	for (i = 0; i < 8; i++) {
		if (mask & (1 << i)) {
			if (!(data & (1 << i))) {
				temp &= ~(type << (i * 4));
				continue;
			}
			temp |= type << (i * 4);
		}
	}
	nvkm_wr32(device, 0x00dc68, temp);
}