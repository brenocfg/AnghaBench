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
struct ov772x_priv {int power_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  win; int /*<<< orphan*/  cfmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov772x_power_off (struct ov772x_priv*) ; 
 int ov772x_power_on (struct ov772x_priv*) ; 
 int ov772x_set_params (struct ov772x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ov772x_priv* to_ov772x (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov772x_s_power(struct v4l2_subdev *sd, int on)
{
	struct ov772x_priv *priv = to_ov772x(sd);
	int ret = 0;

	mutex_lock(&priv->lock);

	/* If the power count is modified from 0 to != 0 or from != 0 to 0,
	 * update the power state.
	 */
	if (priv->power_count == !on) {
		if (on) {
			ret = ov772x_power_on(priv);
			/*
			 * Restore the format, the frame rate, and
			 * the controls
			 */
			if (!ret)
				ret = ov772x_set_params(priv, priv->cfmt,
							priv->win);
		} else {
			ret = ov772x_power_off(priv);
		}
	}

	if (!ret) {
		/* Update the power count. */
		priv->power_count += on ? 1 : -1;
		WARN(priv->power_count < 0, "Unbalanced power count\n");
		WARN(priv->power_count > 1, "Duplicated s_power call\n");
	}

	mutex_unlock(&priv->lock);

	return ret;
}