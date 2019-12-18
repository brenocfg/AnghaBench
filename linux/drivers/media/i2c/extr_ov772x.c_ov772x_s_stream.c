#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct ov772x_priv {int streaming; int /*<<< orphan*/  lock; TYPE_2__* win; TYPE_1__* cfmt; int /*<<< orphan*/  regmap; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM2 ; 
 int /*<<< orphan*/  SOFT_SLEEP_MODE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ov772x_priv* to_ov772x (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov772x_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov772x_priv *priv = to_ov772x(sd);
	int ret = 0;

	mutex_lock(&priv->lock);

	if (priv->streaming == enable)
		goto done;

	ret = regmap_update_bits(priv->regmap, COM2, SOFT_SLEEP_MODE,
				 enable ? 0 : SOFT_SLEEP_MODE);
	if (ret)
		goto done;

	if (enable) {
		dev_dbg(&client->dev, "format %d, win %s\n",
			priv->cfmt->code, priv->win->name);
	}
	priv->streaming = enable;

done:
	mutex_unlock(&priv->lock);

	return ret;
}