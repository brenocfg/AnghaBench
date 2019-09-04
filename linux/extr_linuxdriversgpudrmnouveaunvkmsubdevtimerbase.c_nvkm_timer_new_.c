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
struct nvkm_timer_func {int dummy; } ;
struct nvkm_timer {int /*<<< orphan*/  lock; int /*<<< orphan*/  alarms; struct nvkm_timer_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nvkm_timer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_timer ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nvkm_timer_new_(const struct nvkm_timer_func *func, struct nvkm_device *device,
		int index, struct nvkm_timer **ptmr)
{
	struct nvkm_timer *tmr;

	if (!(tmr = *ptmr = kzalloc(sizeof(*tmr), GFP_KERNEL)))
		return -ENOMEM;

	nvkm_subdev_ctor(&nvkm_timer, device, index, &tmr->subdev);
	tmr->func = func;
	INIT_LIST_HEAD(&tmr->alarms);
	spin_lock_init(&tmr->lock);
	return 0;
}