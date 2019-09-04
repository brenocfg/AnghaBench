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
 int ENODEV ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static int
nv40_fan_pwm_set(struct nvkm_therm *therm, int line, u32 divs, u32 duty)
{
	struct nvkm_subdev *subdev = &therm->subdev;
	struct nvkm_device *device = subdev->device;
	if (line == 2) {
		nvkm_mask(device, 0x0010f0, 0x7fff7fff, (duty << 16) | divs);
	} else
	if (line == 9) {
		nvkm_wr32(device, 0x0015f8, divs);
		nvkm_mask(device, 0x0015f4, 0x7fffffff, duty);
	} else {
		nvkm_error(subdev, "unknown pwm ctrl for gpio %d\n", line);
		return -ENODEV;
	}

	return 0;
}