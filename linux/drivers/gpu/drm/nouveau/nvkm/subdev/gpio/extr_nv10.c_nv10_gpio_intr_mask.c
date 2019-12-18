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
 int NVKM_GPIO_HI ; 
 int NVKM_GPIO_LO ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv10_gpio_intr_mask(struct nvkm_gpio *gpio, u32 type, u32 mask, u32 data)
{
	struct nvkm_device *device = gpio->subdev.device;
	u32 inte = nvkm_rd32(device, 0x001144);
	if (type & NVKM_GPIO_LO)
		inte = (inte & ~(mask << 16)) | (data << 16);
	if (type & NVKM_GPIO_HI)
		inte = (inte & ~mask) | data;
	nvkm_wr32(device, 0x001144, inte);
}