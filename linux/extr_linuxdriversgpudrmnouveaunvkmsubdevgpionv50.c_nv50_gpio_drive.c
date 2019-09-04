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
 int EINVAL ; 
 scalar_t__ nv50_gpio_location (int,int*,int*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 

int
nv50_gpio_drive(struct nvkm_gpio *gpio, int line, int dir, int out)
{
	struct nvkm_device *device = gpio->subdev.device;
	u32 reg, shift;

	if (nv50_gpio_location(line, &reg, &shift))
		return -EINVAL;

	nvkm_mask(device, reg, 3 << shift, (((dir ^ 1) << 1) | out) << shift);
	return 0;
}