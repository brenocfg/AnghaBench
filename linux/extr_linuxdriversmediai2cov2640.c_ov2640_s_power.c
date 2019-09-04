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
struct ov2640_priv {int power_count; int /*<<< orphan*/  lock; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov2640_set_power (struct ov2640_priv*,int) ; 
 struct ov2640_priv* to_ov2640 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov2640_s_power(struct v4l2_subdev *sd, int on)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov2640_priv *priv = to_ov2640(client);

	mutex_lock(&priv->lock);

	/*
	 * If the power count is modified from 0 to != 0 or from != 0 to 0,
	 * update the power state.
	 */
	if (priv->power_count == !on)
		ov2640_set_power(priv, on);
	priv->power_count += on ? 1 : -1;
	WARN_ON(priv->power_count < 0);
	mutex_unlock(&priv->lock);

	return 0;
}