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
struct nvkm_subdev {TYPE_1__* device; } ;
struct nvkm_gpio {int /*<<< orphan*/  subdev; } ;
struct dcb_gpio_func {int /*<<< orphan*/  line; int /*<<< orphan*/  func; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfgopt; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DCB_GPIO_UNUSED ; 
 int EINVAL ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_reset_ids ; 
 scalar_t__ nvkm_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvkm_error (int /*<<< orphan*/ *,char*) ; 
 struct nvkm_gpio* nvkm_gpio (struct nvkm_subdev*) ; 
 int nvkm_gpio_find (struct nvkm_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dcb_gpio_func*) ; 
 int nvkm_gpio_get (struct nvkm_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_gpio_reset (struct nvkm_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * power_checks ; 

__attribute__((used)) static int
nvkm_gpio_init(struct nvkm_subdev *subdev)
{
	struct nvkm_gpio *gpio = nvkm_gpio(subdev);
	struct dcb_gpio_func func;
	int ret;
	int i;

	if (dmi_check_system(gpio_reset_ids))
		nvkm_gpio_reset(gpio, DCB_GPIO_UNUSED);

	if (nvkm_boolopt(subdev->device->cfgopt, "NvPowerChecks", true)) {
		for (i = 0; i < ARRAY_SIZE(power_checks); ++i) {
			ret = nvkm_gpio_find(gpio, 0, power_checks[i],
					     DCB_GPIO_UNUSED, &func);
			if (ret)
				continue;

			ret = nvkm_gpio_get(gpio, 0, func.func, func.line);
			if (!ret)
				continue;

			nvkm_error(&gpio->subdev,
				   "GPU is missing power, check its power "
				   "cables.  Boot with "
				   "nouveau.config=NvPowerChecks=0 to "
				   "disable.\n");
			return -EINVAL;
		}
	}

	return 0;
}