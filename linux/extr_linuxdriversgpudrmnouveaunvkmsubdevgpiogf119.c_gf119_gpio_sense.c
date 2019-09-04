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
struct nvkm_gpio {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 

int
gf119_gpio_sense(struct nvkm_gpio *gpio, int line)
{
	struct nvkm_device *device = gpio->subdev.device;
	return !!(nvkm_rd32(device, 0x00d610 + (line * 4)) & 0x00004000);
}