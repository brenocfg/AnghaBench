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
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_1__ subdev; } ;
struct nvkm_device {int crystal; } ;

/* Variables and functions */
 int pwm_info (struct nvkm_therm*,int) ; 

int
gf119_fan_pwm_clock(struct nvkm_therm *therm, int line)
{
	struct nvkm_device *device = therm->subdev.device;
	int indx = pwm_info(therm, line);
	if (indx < 0)
		return 0;
	else if (indx < 2)
		return (device->crystal * 1000) / 20;
	else
		return device->crystal * 1000 / 10;
}