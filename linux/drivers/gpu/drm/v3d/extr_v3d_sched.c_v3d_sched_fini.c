#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v3d_dev {TYPE_1__* queue; } ;
typedef  enum v3d_queue { ____Placeholder_v3d_queue } v3d_queue ;
struct TYPE_4__ {scalar_t__ ready; } ;
struct TYPE_3__ {TYPE_2__ sched; } ;

/* Variables and functions */
 int V3D_MAX_QUEUES ; 
 int /*<<< orphan*/  drm_sched_fini (TYPE_2__*) ; 

void
v3d_sched_fini(struct v3d_dev *v3d)
{
	enum v3d_queue q;

	for (q = 0; q < V3D_MAX_QUEUES; q++) {
		if (v3d->queue[q].sched.ready)
			drm_sched_fini(&v3d->queue[q].sched);
	}
}