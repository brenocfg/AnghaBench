#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_async_subdev {int dummy; } ;
struct rvin_dev {TYPE_2__* group; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  num_subdevs; } ;
struct TYPE_7__ {unsigned int count; TYPE_3__ notifier; int /*<<< orphan*/  lock; TYPE_1__** vin; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int RCAR_VIN_NUM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvin_group_notify_ops ; 
 int /*<<< orphan*/  rvin_mc_parse_of_endpoint ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_3__*) ; 
 int v4l2_async_notifier_parse_fwnode_endpoints_by_port (int /*<<< orphan*/ ,TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  vin_err (struct rvin_dev*,char*) ; 

__attribute__((used)) static int rvin_mc_parse_of_graph(struct rvin_dev *vin)
{
	unsigned int count = 0;
	unsigned int i;
	int ret;

	mutex_lock(&vin->group->lock);

	/* If not all VIN's are registered don't register the notifier. */
	for (i = 0; i < RCAR_VIN_NUM; i++)
		if (vin->group->vin[i])
			count++;

	if (vin->group->count != count) {
		mutex_unlock(&vin->group->lock);
		return 0;
	}

	/*
	 * Have all VIN's look for CSI-2 subdevices. Some subdevices will
	 * overlap but the parser function can handle it, so each subdevice
	 * will only be registered once with the group notifier.
	 */
	for (i = 0; i < RCAR_VIN_NUM; i++) {
		if (!vin->group->vin[i])
			continue;

		ret = v4l2_async_notifier_parse_fwnode_endpoints_by_port(
				vin->group->vin[i]->dev, &vin->group->notifier,
				sizeof(struct v4l2_async_subdev), 1,
				rvin_mc_parse_of_endpoint);
		if (ret) {
			mutex_unlock(&vin->group->lock);
			return ret;
		}
	}

	mutex_unlock(&vin->group->lock);

	if (!vin->group->notifier.num_subdevs)
		return 0;

	vin->group->notifier.ops = &rvin_group_notify_ops;
	ret = v4l2_async_notifier_register(&vin->v4l2_dev,
					   &vin->group->notifier);
	if (ret < 0) {
		vin_err(vin, "Notifier registration failed\n");
		v4l2_async_notifier_cleanup(&vin->group->notifier);
		return ret;
	}

	return 0;
}