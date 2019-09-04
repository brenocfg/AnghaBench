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
struct nvkm_subdev {TYPE_1__* func; } ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {struct nvkm_subdev* (* dtor ) (struct nvkm_subdev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_trace (struct nvkm_subdev*,char*,...) ; 
 struct nvkm_subdev* stub1 (struct nvkm_subdev*) ; 

void
nvkm_subdev_del(struct nvkm_subdev **psubdev)
{
	struct nvkm_subdev *subdev = *psubdev;
	s64 time;

	if (subdev && !WARN_ON(!subdev->func)) {
		nvkm_trace(subdev, "destroy running...\n");
		time = ktime_to_us(ktime_get());
		if (subdev->func->dtor)
			*psubdev = subdev->func->dtor(subdev);
		time = ktime_to_us(ktime_get()) - time;
		nvkm_trace(subdev, "destroy completed in %lldus\n", time);
		kfree(*psubdev);
		*psubdev = NULL;
	}
}