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
struct TYPE_6__ {int /*<<< orphan*/ * ctrl_handler; } ;
struct rvin_dev {TYPE_3__ vdev; int /*<<< orphan*/  ctrl_handler; TYPE_2__* info; TYPE_1__* parallel; } ;
struct TYPE_5__ {int /*<<< orphan*/  use_mc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  rvin_v4l2_unregister (struct rvin_dev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rvin_parallel_subdevice_detach(struct rvin_dev *vin)
{
	rvin_v4l2_unregister(vin);
	vin->parallel->subdev = NULL;

	if (!vin->info->use_mc) {
		v4l2_ctrl_handler_free(&vin->ctrl_handler);
		vin->vdev.ctrl_handler = NULL;
	}
}