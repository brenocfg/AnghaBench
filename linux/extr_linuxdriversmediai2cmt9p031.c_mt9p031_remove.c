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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct mt9p031 {int /*<<< orphan*/  power_lock; int /*<<< orphan*/  ctrls; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct mt9p031* to_mt9p031 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9p031_remove(struct i2c_client *client)
{
	struct v4l2_subdev *subdev = i2c_get_clientdata(client);
	struct mt9p031 *mt9p031 = to_mt9p031(subdev);

	v4l2_ctrl_handler_free(&mt9p031->ctrls);
	v4l2_async_unregister_subdev(subdev);
	media_entity_cleanup(&subdev->entity);
	mutex_destroy(&mt9p031->power_lock);

	return 0;
}