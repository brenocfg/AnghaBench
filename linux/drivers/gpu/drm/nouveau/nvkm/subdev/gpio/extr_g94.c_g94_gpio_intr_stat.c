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
struct nvkm_gpio {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
g94_gpio_intr_stat(struct nvkm_gpio *gpio, u32 *hi, u32 *lo)
{
	struct nvkm_device *device = gpio->subdev.device;
	u32 intr0 = nvkm_rd32(device, 0x00e054);
	u32 intr1 = nvkm_rd32(device, 0x00e074);
	u32 stat0 = nvkm_rd32(device, 0x00e050) & intr0;
	u32 stat1 = nvkm_rd32(device, 0x00e070) & intr1;
	*lo = (stat1 & 0xffff0000) | (stat0 >> 16);
	*hi = (stat1 << 16) | (stat0 & 0x0000ffff);
	nvkm_wr32(device, 0x00e054, intr0);
	nvkm_wr32(device, 0x00e074, intr1);
}