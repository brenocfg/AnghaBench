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
struct nvkm_timer {int dummy; } ;
struct nvkm_subdev {TYPE_1__* device; } ;
struct nvkm_therm {int mode; int cstate; int /*<<< orphan*/  lock; int /*<<< orphan*/  alarm; TYPE_3__* fan; struct nvkm_subdev subdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  fan_mode; } ;
struct TYPE_6__ {TYPE_2__ bios; } ;
struct TYPE_4__ {struct nvkm_timer* timer; } ;

/* Variables and functions */
#define  NVBIOS_THERM_FAN_LINEAR 133 
#define  NVBIOS_THERM_FAN_OTHER 132 
#define  NVBIOS_THERM_FAN_TRIP 131 
#define  NVKM_THERM_CTRL_AUTO 130 
#define  NVKM_THERM_CTRL_MANUAL 129 
#define  NVKM_THERM_CTRL_NONE 128 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int) ; 
 int nvkm_therm_fan_get (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_therm_fan_set (struct nvkm_therm*,int,int) ; 
 int nvkm_therm_update_linear (struct nvkm_therm*) ; 
 int nvkm_therm_update_linear_fallback (struct nvkm_therm*) ; 
 int nvkm_therm_update_trip (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_timer_alarm (struct nvkm_timer*,unsigned long long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nvkm_therm_update(struct nvkm_therm *therm, int mode)
{
	struct nvkm_subdev *subdev = &therm->subdev;
	struct nvkm_timer *tmr = subdev->device->timer;
	unsigned long flags;
	bool immd = true;
	bool poll = true;
	int duty = -1;

	spin_lock_irqsave(&therm->lock, flags);
	if (mode < 0)
		mode = therm->mode;
	therm->mode = mode;

	switch (mode) {
	case NVKM_THERM_CTRL_MANUAL:
		nvkm_timer_alarm(tmr, 0, &therm->alarm);
		duty = nvkm_therm_fan_get(therm);
		if (duty < 0)
			duty = 100;
		poll = false;
		break;
	case NVKM_THERM_CTRL_AUTO:
		switch(therm->fan->bios.fan_mode) {
		case NVBIOS_THERM_FAN_TRIP:
			duty = nvkm_therm_update_trip(therm);
			break;
		case NVBIOS_THERM_FAN_LINEAR:
			duty = nvkm_therm_update_linear(therm);
			break;
		case NVBIOS_THERM_FAN_OTHER:
			if (therm->cstate) {
				duty = therm->cstate;
				poll = false;
			} else {
				duty = nvkm_therm_update_linear_fallback(therm);
			}
			break;
		}
		immd = false;
		break;
	case NVKM_THERM_CTRL_NONE:
	default:
		nvkm_timer_alarm(tmr, 0, &therm->alarm);
		poll = false;
	}

	if (poll)
		nvkm_timer_alarm(tmr, 1000000000ULL, &therm->alarm);
	spin_unlock_irqrestore(&therm->lock, flags);

	if (duty >= 0) {
		nvkm_debug(subdev, "FAN target request: %d%%\n", duty);
		nvkm_therm_fan_set(therm, immd, duty);
	}
}