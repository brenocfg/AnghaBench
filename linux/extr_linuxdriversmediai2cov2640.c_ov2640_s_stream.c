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
struct ov2640_priv {int streaming; int /*<<< orphan*/  lock; int /*<<< orphan*/  hdl; int /*<<< orphan*/  cfmt_code; int /*<<< orphan*/  win; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int __v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov2640_set_params (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ov2640_priv* to_ov2640 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov2640_s_stream(struct v4l2_subdev *sd, int on)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov2640_priv *priv = to_ov2640(client);
	int ret = 0;

	mutex_lock(&priv->lock);
	if (priv->streaming == !on) {
		if (on) {
			ret = ov2640_set_params(client, priv->win,
						priv->cfmt_code);
			if (!ret)
				ret = __v4l2_ctrl_handler_setup(&priv->hdl);
		}
	}
	if (!ret)
		priv->streaming = on;
	mutex_unlock(&priv->lock);

	return ret;
}