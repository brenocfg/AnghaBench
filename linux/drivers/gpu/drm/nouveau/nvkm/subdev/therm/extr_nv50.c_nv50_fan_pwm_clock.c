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
typedef  int u8 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_1__ subdev; } ;
struct nvkm_device {int chipset; int crystal; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 

int
nv50_fan_pwm_clock(struct nvkm_therm *therm, int line)
{
	struct nvkm_device *device = therm->subdev.device;
	int pwm_clock;

	/* determine the PWM source clock */
	if (device->chipset > 0x50 && device->chipset < 0x94) {
		u8 pwm_div = nvkm_rd32(device, 0x410c);
		if (nvkm_rd32(device, 0xc040) & 0x800000) {
			/* Use the HOST clock (100 MHz)
			* Where does this constant(2.4) comes from? */
			pwm_clock = (100000000 >> pwm_div) * 10 / 24;
		} else {
			/* Where does this constant(20) comes from? */
			pwm_clock = (device->crystal * 1000) >> pwm_div;
			pwm_clock /= 20;
		}
	} else {
		pwm_clock = (device->crystal * 1000) / 20;
	}

	return pwm_clock;
}