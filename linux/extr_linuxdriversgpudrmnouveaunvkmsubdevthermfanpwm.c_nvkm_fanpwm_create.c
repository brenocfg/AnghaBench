#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_3__* fan; TYPE_2__* func; TYPE_1__ subdev; } ;
struct dcb_gpio_func {int /*<<< orphan*/  line; int /*<<< orphan*/  param; } ;
struct TYPE_6__ {char* type; int /*<<< orphan*/  set; int /*<<< orphan*/  get; } ;
struct nvkm_fanpwm {struct dcb_gpio_func func; TYPE_3__ base; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_therm_fan {scalar_t__ type; } ;
struct TYPE_5__ {int (* pwm_get ) (struct nvkm_therm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  pwm_ctrl; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NVBIOS_THERM_FAN_TOGGLE ; 
 struct nvkm_fanpwm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvbios_fan_parse (struct nvkm_bios*,struct nvbios_therm_fan*) ; 
 int /*<<< orphan*/  nvkm_boolopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_fanpwm_get ; 
 int /*<<< orphan*/  nvkm_fanpwm_set ; 
 int stub1 (struct nvkm_therm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nvkm_fanpwm_create(struct nvkm_therm *therm, struct dcb_gpio_func *func)
{
	struct nvkm_device *device = therm->subdev.device;
	struct nvkm_bios *bios = device->bios;
	struct nvkm_fanpwm *fan;
	struct nvbios_therm_fan info = {};
	u32 divs, duty;

	nvbios_fan_parse(bios, &info);

	if (!nvkm_boolopt(device->cfgopt, "NvFanPWM", func->param) ||
	    !therm->func->pwm_ctrl || info.type == NVBIOS_THERM_FAN_TOGGLE ||
	     therm->func->pwm_get(therm, func->line, &divs, &duty) == -ENODEV)
		return -ENODEV;

	fan = kzalloc(sizeof(*fan), GFP_KERNEL);
	therm->fan = &fan->base;
	if (!fan)
		return -ENOMEM;

	fan->base.type = "PWM";
	fan->base.get = nvkm_fanpwm_get;
	fan->base.set = nvkm_fanpwm_set;
	fan->func = *func;
	return 0;
}