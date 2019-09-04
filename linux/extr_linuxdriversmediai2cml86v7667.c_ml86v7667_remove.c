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
struct v4l2_subdev {int dummy; } ;
struct ml86v7667_priv {int /*<<< orphan*/  sd; int /*<<< orphan*/  hdl; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 struct ml86v7667_priv* to_ml86v7667 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ml86v7667_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct ml86v7667_priv *priv = to_ml86v7667(sd);

	v4l2_ctrl_handler_free(&priv->hdl);
	v4l2_device_unregister_subdev(&priv->sd);

	return 0;
}