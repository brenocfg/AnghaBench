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

__attribute__((used)) static int
nv40_fan_pwm_ctrl(struct nvkm_therm *therm, int line, bool enable)
{
	struct nvkm_subdev *subdev = &therm->subdev;
	struct nvkm_device *device = subdev->device;
	u32 mask = enable ? 0x80000000 : 0x00000000;
	if      (line == 2) nvkm_mask(device, 0x0010f0, 0x80000000, mask);
	else if (line == 9) nvkm_mask(device, 0x0015f4, 0x80000000, mask);
	else {
		nvkm_error(subdev, "unknown pwm ctrl for gpio %d\n", line);
		return -ENODEV;
	}
	return 0;
}