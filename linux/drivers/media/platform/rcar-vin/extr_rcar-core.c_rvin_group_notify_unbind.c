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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ fwnode; } ;
struct v4l2_async_subdev {TYPE_1__ match; } ;
struct v4l2_async_notifier {int /*<<< orphan*/  v4l2_dev; } ;
struct rvin_dev {TYPE_3__* group; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__* csi; scalar_t__* vin; } ;
struct TYPE_5__ {scalar_t__ fwnode; int /*<<< orphan*/ * subdev; } ;

/* Variables and functions */
 unsigned int RCAR_VIN_NUM ; 
 unsigned int RVIN_CSI_MAX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvin_v4l2_unregister (scalar_t__) ; 
 struct rvin_dev* v4l2_dev_to_vin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void rvin_group_notify_unbind(struct v4l2_async_notifier *notifier,
				     struct v4l2_subdev *subdev,
				     struct v4l2_async_subdev *asd)
{
	struct rvin_dev *vin = v4l2_dev_to_vin(notifier->v4l2_dev);
	unsigned int i;

	for (i = 0; i < RCAR_VIN_NUM; i++)
		if (vin->group->vin[i])
			rvin_v4l2_unregister(vin->group->vin[i]);

	mutex_lock(&vin->group->lock);

	for (i = 0; i < RVIN_CSI_MAX; i++) {
		if (vin->group->csi[i].fwnode != asd->match.fwnode)
			continue;
		vin->group->csi[i].subdev = NULL;
		vin_dbg(vin, "Unbind CSI-2 %s from slot %u\n", subdev->name, i);
		break;
	}

	mutex_unlock(&vin->group->lock);
}