#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_therm {struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static int
nv40_fan_pwm_get(struct nvkm_therm *therm, int line, u32 *divs, u32 *duty)
{
	struct nvkm_subdev *subdev = &therm->subdev;
	struct nvkm_device *device = subdev->device;
	if (line == 2) {
		u32 reg = nvkm_rd32(device, 0x0010f0);
		if (reg & 0x80000000) {
			*duty = (reg & 0x7fff0000) >> 16;
			*divs = (reg & 0x00007fff);
			return 0;
		}
	} else
	if (line == 9) {
		u32 reg = nvkm_rd32(device, 0x0015f4);
		if (reg & 0x80000000) {
			*divs = nvkm_rd32(device, 0x0015f8);
			*duty = (reg & 0x7fffffff);
			return 0;
		}
	} else {
		nvkm_error(subdev, "unknown pwm ctrl for gpio %d\n", line);
		return -ENODEV;
	}

	return -EINVAL;
}