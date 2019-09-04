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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_1__* fan; struct nvkm_subdev subdev; } ;
struct nvkm_gpio {int dummy; } ;
struct nvkm_device {struct nvkm_bios* bios; struct nvkm_gpio* gpio; } ;
struct nvkm_bios {int dummy; } ;
struct dcb_gpio_func {int line; int* log; int /*<<< orphan*/  func; } ;
struct TYPE_2__ {int /*<<< orphan*/  bios; int /*<<< orphan*/  perf; int /*<<< orphan*/  lock; int /*<<< orphan*/  alarm; struct nvkm_therm* parent; struct dcb_gpio_func tach; int /*<<< orphan*/  percent; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_GPIO_FAN ; 
 int /*<<< orphan*/  DCB_GPIO_FAN_SENSE ; 
 int DCB_GPIO_LOG_DIR_IN ; 
 int /*<<< orphan*/  DCB_GPIO_UNUSED ; 
 int EINVAL ; 
 int /*<<< orphan*/  nvbios_fan_parse (struct nvkm_bios*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvbios_perf_fan_parse (struct nvkm_bios*,int /*<<< orphan*/ *) ; 
 scalar_t__ nvbios_therm_fan_parse (struct nvkm_bios*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_alarm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,...) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_fan_alarm ; 
 int nvkm_fannil_create (struct nvkm_therm*) ; 
 int nvkm_fanpwm_create (struct nvkm_therm*,struct dcb_gpio_func*) ; 
 int nvkm_fantog_create (struct nvkm_therm*,struct dcb_gpio_func*) ; 
 int nvkm_gpio_find (struct nvkm_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dcb_gpio_func*) ; 
 int /*<<< orphan*/  nvkm_therm_fan_get (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_therm_fan_safety_checks (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_therm_fan_set_defaults (struct nvkm_therm*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nvkm_therm_fan_ctor(struct nvkm_therm *therm)
{
	struct nvkm_subdev *subdev = &therm->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_gpio *gpio = device->gpio;
	struct nvkm_bios *bios = device->bios;
	struct dcb_gpio_func func;
	int ret;

	/* attempt to locate a drivable fan, and determine control method */
	ret = nvkm_gpio_find(gpio, 0, DCB_GPIO_FAN, 0xff, &func);
	if (ret == 0) {
		/* FIXME: is this really the place to perform such checks ? */
		if (func.line != 16 && func.log[0] & DCB_GPIO_LOG_DIR_IN) {
			nvkm_debug(subdev, "GPIO_FAN is in input mode\n");
			ret = -EINVAL;
		} else {
			ret = nvkm_fanpwm_create(therm, &func);
			if (ret != 0)
				ret = nvkm_fantog_create(therm, &func);
		}
	}

	/* no controllable fan found, create a dummy fan module */
	if (ret != 0) {
		ret = nvkm_fannil_create(therm);
		if (ret)
			return ret;
	}

	nvkm_debug(subdev, "FAN control: %s\n", therm->fan->type);

	/* read the current speed, it is useful when resuming */
	therm->fan->percent = nvkm_therm_fan_get(therm);

	/* attempt to detect a tachometer connection */
	ret = nvkm_gpio_find(gpio, 0, DCB_GPIO_FAN_SENSE, 0xff,
			     &therm->fan->tach);
	if (ret)
		therm->fan->tach.func = DCB_GPIO_UNUSED;

	/* initialise fan bump/slow update handling */
	therm->fan->parent = therm;
	nvkm_alarm_init(&therm->fan->alarm, nvkm_fan_alarm);
	spin_lock_init(&therm->fan->lock);

	/* other random init... */
	nvkm_therm_fan_set_defaults(therm);
	nvbios_perf_fan_parse(bios, &therm->fan->perf);
	if (!nvbios_fan_parse(bios, &therm->fan->bios)) {
		nvkm_debug(subdev, "parsing the fan table failed\n");
		if (nvbios_therm_fan_parse(bios, &therm->fan->bios))
			nvkm_error(subdev, "parsing both fan tables failed\n");
	}
	nvkm_therm_fan_safety_checks(therm);
	return 0;
}