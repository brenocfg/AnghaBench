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
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct mipid02_dev {int /*<<< orphan*/  lock; TYPE_1__ sd; int /*<<< orphan*/  notifier; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mipid02_set_power_off (struct mipid02_dev*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct mipid02_dev* to_mipid02_dev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (TYPE_1__*) ; 

__attribute__((used)) static int mipid02_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct mipid02_dev *bridge = to_mipid02_dev(sd);

	v4l2_async_notifier_unregister(&bridge->notifier);
	v4l2_async_notifier_cleanup(&bridge->notifier);
	v4l2_async_unregister_subdev(&bridge->sd);
	mipid02_set_power_off(bridge);
	media_entity_cleanup(&bridge->sd.entity);
	mutex_destroy(&bridge->lock);

	return 0;
}