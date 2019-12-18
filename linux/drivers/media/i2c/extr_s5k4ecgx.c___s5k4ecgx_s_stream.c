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
struct s5k4ecgx {scalar_t__ set_params; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_G_ENABLE_PREV ; 
 int /*<<< orphan*/  REG_G_ENABLE_PREV_CHG ; 
 int __s5k4ecgx_s_params (struct s5k4ecgx*) ; 
 int s5k4ecgx_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __s5k4ecgx_s_stream(struct s5k4ecgx *priv, int on)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->sd);
	int ret;

	if (on && priv->set_params) {
		ret = __s5k4ecgx_s_params(priv);
		if (ret < 0)
			return ret;
		priv->set_params = 0;
	}
	/*
	 * This enables/disables preview stream only. Capture requests
	 * are not supported yet.
	 */
	ret = s5k4ecgx_write(client, REG_G_ENABLE_PREV, on);
	if (ret < 0)
		return ret;
	return s5k4ecgx_write(client, REG_G_ENABLE_PREV_CHG, 1);
}