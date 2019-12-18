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
gk104_aux_stat(struct nvkm_i2c *i2c, u32 *hi, u32 *lo, u32 *rq, u32 *tx)
{
	struct nvkm_device *device = i2c->subdev.device;
	u32 intr = nvkm_rd32(device, 0x00dc60);
	u32 stat = nvkm_rd32(device, 0x00dc68) & intr, i;
	for (i = 0, *hi = *lo = *rq = *tx = 0; i < 8; i++) {
		if ((stat & (1 << (i * 4)))) *hi |= 1 << i;
		if ((stat & (2 << (i * 4)))) *lo |= 1 << i;
		if ((stat & (4 << (i * 4)))) *rq |= 1 << i;
		if ((stat & (8 << (i * 4)))) *tx |= 1 << i;
	}
	nvkm_wr32(device, 0x00dc60, intr);
}