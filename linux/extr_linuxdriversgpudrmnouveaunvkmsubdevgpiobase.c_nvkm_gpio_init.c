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
struct nvkm_subdev {int dummy; } ;
struct nvkm_gpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_GPIO_UNUSED ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_reset_ids ; 
 struct nvkm_gpio* nvkm_gpio (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_gpio_reset (struct nvkm_gpio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_gpio_init(struct nvkm_subdev *subdev)
{
	struct nvkm_gpio *gpio = nvkm_gpio(subdev);
	if (dmi_check_system(gpio_reset_ids))
		nvkm_gpio_reset(gpio, DCB_GPIO_UNUSED);
	return 0;
}