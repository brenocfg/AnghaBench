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
typedef  int u8 ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct nvkm_volt {int vid_mask; TYPE_2__ subdev; } ;
struct nvkm_gpio {int dummy; } ;
struct TYPE_3__ {struct nvkm_gpio* gpio; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int nvkm_gpio_get (struct nvkm_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * tags ; 

int
nvkm_voltgpio_get(struct nvkm_volt *volt)
{
	struct nvkm_gpio *gpio = volt->subdev.device->gpio;
	u8 vid = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(tags); i++) {
		if (volt->vid_mask & (1 << i)) {
			int ret = nvkm_gpio_get(gpio, 0, tags[i], 0xff);
			if (ret < 0)
				return ret;
			vid |= ret << i;
		}
	}

	return vid;
}