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
struct nvbios_therm_sensor {int slope_div; int slope_mult; int offset_num; int offset_den; int offset_constant; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_therm {struct nvbios_therm_sensor bios_sensor; TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static int
nv50_temp_get(struct nvkm_therm *therm)
{
	struct nvkm_device *device = therm->subdev.device;
	struct nvbios_therm_sensor *sensor = &therm->bios_sensor;
	int core_temp;

	core_temp = nvkm_rd32(device, 0x20014) & 0x3fff;

	/* if the slope or the offset is unset, do no use the sensor */
	if (!sensor->slope_div || !sensor->slope_mult ||
	    !sensor->offset_num || !sensor->offset_den)
	    return -ENODEV;

	core_temp = core_temp * sensor->slope_mult / sensor->slope_div;
	core_temp = core_temp + sensor->offset_num / sensor->offset_den;
	core_temp = core_temp + sensor->offset_constant - 8;

	/* reserve negative temperatures for errors */
	if (core_temp < 0)
		core_temp = 0;

	return core_temp;
}