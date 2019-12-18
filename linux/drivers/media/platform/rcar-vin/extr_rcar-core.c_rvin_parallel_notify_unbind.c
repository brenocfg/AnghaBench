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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int /*<<< orphan*/  v4l2_dev; } ;
struct rvin_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvin_parallel_subdevice_detach (struct rvin_dev*) ; 
 struct rvin_dev* v4l2_dev_to_vin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvin_parallel_notify_unbind(struct v4l2_async_notifier *notifier,
					struct v4l2_subdev *subdev,
					struct v4l2_async_subdev *asd)
{
	struct rvin_dev *vin = v4l2_dev_to_vin(notifier->v4l2_dev);

	vin_dbg(vin, "unbind parallel subdev %s\n", subdev->name);

	mutex_lock(&vin->lock);
	rvin_parallel_subdevice_detach(vin);
	mutex_unlock(&vin->lock);
}