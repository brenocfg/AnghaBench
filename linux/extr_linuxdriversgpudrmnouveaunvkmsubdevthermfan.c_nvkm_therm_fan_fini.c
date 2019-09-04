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
struct TYPE_5__ {TYPE_1__* device; } ;
struct nvkm_therm {TYPE_3__* fan; TYPE_2__ subdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  alarm; } ;
struct TYPE_4__ {struct nvkm_timer* timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_timer_alarm (struct nvkm_timer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nvkm_therm_fan_fini(struct nvkm_therm *therm, bool suspend)
{
	struct nvkm_timer *tmr = therm->subdev.device->timer;
	if (suspend)
		nvkm_timer_alarm(tmr, 0, &therm->fan->alarm);
	return 0;
}