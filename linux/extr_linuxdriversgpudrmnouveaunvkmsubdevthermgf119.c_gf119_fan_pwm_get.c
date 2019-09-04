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
struct nvkm_therm {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int pwm_info (struct nvkm_therm*,int) ; 

int
gf119_fan_pwm_get(struct nvkm_therm *therm, int line, u32 *divs, u32 *duty)
{
	struct nvkm_device *device = therm->subdev.device;
	int indx = pwm_info(therm, line);
	if (indx < 0)
		return indx;
	else if (indx < 2) {
		if (nvkm_rd32(device, 0x00d610 + (line * 0x04)) & 0x00000040) {
			*divs = nvkm_rd32(device, 0x00e114 + (indx * 8));
			*duty = nvkm_rd32(device, 0x00e118 + (indx * 8));
			return 0;
		}
	} else if (indx == 2) {
		*divs = nvkm_rd32(device, 0x0200d8) & 0x1fff;
		*duty = nvkm_rd32(device, 0x0200dc) & 0x1fff;
		return 0;
	}

	return -EINVAL;
}