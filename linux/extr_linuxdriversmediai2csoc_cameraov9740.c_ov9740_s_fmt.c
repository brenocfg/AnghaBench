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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ov9740_priv {struct v4l2_mbus_framefmt current_mf; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov9740_defaults ; 
 int ov9740_reg_write_array (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov9740_set_res (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ov9740_priv* to_ov9740 (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov9740_s_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov9740_priv *priv = to_ov9740(sd);
	int ret;

	ret = ov9740_reg_write_array(client, ov9740_defaults,
				     ARRAY_SIZE(ov9740_defaults));
	if (ret < 0)
		return ret;

	ret = ov9740_set_res(client, mf->width, mf->height);
	if (ret < 0)
		return ret;

	priv->current_mf = *mf;
	return ret;
}