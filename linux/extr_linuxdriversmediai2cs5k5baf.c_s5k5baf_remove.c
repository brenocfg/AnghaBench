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
struct v4l2_subdev {int /*<<< orphan*/  entity; int /*<<< orphan*/  ctrl_handler; } ;
struct s5k5baf {struct v4l2_subdev cis_sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 struct s5k5baf* to_s5k5baf (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k5baf_remove(struct i2c_client *c)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(c);
	struct s5k5baf *state = to_s5k5baf(sd);

	v4l2_async_unregister_subdev(sd);
	v4l2_ctrl_handler_free(sd->ctrl_handler);
	media_entity_cleanup(&sd->entity);

	sd = &state->cis_sd;
	v4l2_device_unregister_subdev(sd);
	media_entity_cleanup(&sd->entity);

	return 0;
}