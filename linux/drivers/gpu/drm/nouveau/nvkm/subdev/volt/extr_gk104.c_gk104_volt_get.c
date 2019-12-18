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
typedef  int u32 ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct nvkm_volt {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;
struct nvbios_volt {int base; int pwm_range; } ;
struct TYPE_4__ {struct nvbios_volt bios; } ;

/* Variables and functions */
 TYPE_2__* gk104_volt (struct nvkm_volt*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static int
gk104_volt_get(struct nvkm_volt *base)
{
	struct nvbios_volt *bios = &gk104_volt(base)->bios;
	struct nvkm_device *device = base->subdev.device;
	u32 div, duty;

	div  = nvkm_rd32(device, 0x20340);
	duty = nvkm_rd32(device, 0x20344);

	return bios->base + bios->pwm_range * duty / div;
}