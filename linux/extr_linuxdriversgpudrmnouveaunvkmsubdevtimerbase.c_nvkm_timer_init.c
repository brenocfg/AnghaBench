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
struct nvkm_timer {TYPE_1__* func; } ;
struct nvkm_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* time ) (struct nvkm_timer*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init ) (struct nvkm_timer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 struct nvkm_timer* nvkm_timer (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_timer_alarm_trigger (struct nvkm_timer*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_timer*) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_timer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_timer_init(struct nvkm_subdev *subdev)
{
	struct nvkm_timer *tmr = nvkm_timer(subdev);
	if (tmr->func->init)
		tmr->func->init(tmr);
	tmr->func->time(tmr, ktime_to_ns(ktime_get()));
	nvkm_timer_alarm_trigger(tmr);
	return 0;
}