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
struct nvkm_therm_func {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  alarm_program_lock; } ;
struct nvkm_therm {int mode; int suspend; int /*<<< orphan*/  clkgating_enabled; int /*<<< orphan*/  attr_set; int /*<<< orphan*/  attr_get; int /*<<< orphan*/  fan_set; int /*<<< orphan*/  fan_get; TYPE_1__ sensor; int /*<<< orphan*/  lock; int /*<<< orphan*/  alarm; struct nvkm_therm_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_alarm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_therm ; 
 int /*<<< orphan*/  nvkm_therm_alarm ; 
 int /*<<< orphan*/  nvkm_therm_attr_get ; 
 int /*<<< orphan*/  nvkm_therm_attr_set ; 
 int /*<<< orphan*/  nvkm_therm_fan_user_get ; 
 int /*<<< orphan*/  nvkm_therm_fan_user_set ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void
nvkm_therm_ctor(struct nvkm_therm *therm, struct nvkm_device *device,
		int index, const struct nvkm_therm_func *func)
{
	nvkm_subdev_ctor(&nvkm_therm, device, index, &therm->subdev);
	therm->func = func;

	nvkm_alarm_init(&therm->alarm, nvkm_therm_alarm);
	spin_lock_init(&therm->lock);
	spin_lock_init(&therm->sensor.alarm_program_lock);

	therm->fan_get = nvkm_therm_fan_user_get;
	therm->fan_set = nvkm_therm_fan_user_set;
	therm->attr_get = nvkm_therm_attr_get;
	therm->attr_set = nvkm_therm_attr_set;
	therm->mode = therm->suspend = -1; /* undefined */

	therm->clkgating_enabled = nvkm_boolopt(device->cfgopt,
						"NvPmEnableGating", false);
}