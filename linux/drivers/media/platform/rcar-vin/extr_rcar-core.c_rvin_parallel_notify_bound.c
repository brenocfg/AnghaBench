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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int /*<<< orphan*/  v4l2_dev; } ;
struct rvin_dev {TYPE_1__* parallel; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  sink_pad; int /*<<< orphan*/  source_pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rvin_parallel_subdevice_attach (struct rvin_dev*,struct v4l2_subdev*) ; 
 struct rvin_dev* v4l2_dev_to_vin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_set_subdev_hostdata (struct v4l2_subdev*,struct rvin_dev*) ; 
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvin_parallel_notify_bound(struct v4l2_async_notifier *notifier,
				      struct v4l2_subdev *subdev,
				      struct v4l2_async_subdev *asd)
{
	struct rvin_dev *vin = v4l2_dev_to_vin(notifier->v4l2_dev);
	int ret;

	mutex_lock(&vin->lock);
	ret = rvin_parallel_subdevice_attach(vin, subdev);
	mutex_unlock(&vin->lock);
	if (ret)
		return ret;

	v4l2_set_subdev_hostdata(subdev, vin);

	vin_dbg(vin, "bound subdev %s source pad: %u sink pad: %u\n",
		subdev->name, vin->parallel->source_pad,
		vin->parallel->sink_pad);

	return 0;
}