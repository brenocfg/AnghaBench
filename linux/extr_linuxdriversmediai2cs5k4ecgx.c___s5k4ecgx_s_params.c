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
struct v4l2_rect {int dummy; } ;
struct s5k4ecgx {TYPE_1__* curr_frmsize; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {struct v4l2_rect input_window; } ;

/* Variables and functions */
 int FR_TIME_DYNAMIC ; 
 int FR_TIME_Q_BEST_FRRATE ; 
 int REG_G_ACTIVE_PREV_CFG ; 
 int REG_G_INPUTS_CHANGE_REQ ; 
 int REG_G_NEW_CFG_SYNC ; 
 int REG_G_PREV_CFG_CHG ; 
 int REG_G_PREV_OPEN_AFTER_CH ; 
 int REG_P_CAP_MIRROR (int /*<<< orphan*/ ) ; 
 int REG_P_FR_TIME_Q_TYPE (int /*<<< orphan*/ ) ; 
 int REG_P_FR_TIME_TYPE (int /*<<< orphan*/ ) ; 
 int REG_P_MAX_FR_TIME (int /*<<< orphan*/ ) ; 
 int REG_P_MIN_FR_TIME (int /*<<< orphan*/ ) ; 
 int REG_P_PREV_MIRROR (int /*<<< orphan*/ ) ; 
 int REG_P_PVI_MASK (int /*<<< orphan*/ ) ; 
 int US_TO_FR_TIME (int) ; 
 int s5k4ecgx_set_input_window (struct i2c_client*,struct v4l2_rect const*) ; 
 int s5k4ecgx_set_output_framefmt (struct s5k4ecgx*) ; 
 int s5k4ecgx_set_zoom_window (struct i2c_client*,struct v4l2_rect const*) ; 
 int s5k4ecgx_write (struct i2c_client*,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __s5k4ecgx_s_params(struct s5k4ecgx *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->sd);
	const struct v4l2_rect *crop_rect = &priv->curr_frmsize->input_window;
	int ret;

	ret = s5k4ecgx_set_input_window(client, crop_rect);
	if (!ret)
		ret = s5k4ecgx_set_zoom_window(client, crop_rect);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_G_INPUTS_CHANGE_REQ, 1);
	if (!ret)
		ret = s5k4ecgx_write(client, 0x70000a1e, 0x28);
	if (!ret)
		ret = s5k4ecgx_write(client, 0x70000ad4, 0x3c);
	if (!ret)
		ret = s5k4ecgx_set_output_framefmt(priv);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_P_PVI_MASK(0), 0x52);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_P_FR_TIME_TYPE(0),
				     FR_TIME_DYNAMIC);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_P_FR_TIME_Q_TYPE(0),
				     FR_TIME_Q_BEST_FRRATE);
	if (!ret)
		ret = s5k4ecgx_write(client,  REG_P_MIN_FR_TIME(0),
				     US_TO_FR_TIME(33300));
	if (!ret)
		ret = s5k4ecgx_write(client, REG_P_MAX_FR_TIME(0),
				     US_TO_FR_TIME(66600));
	if (!ret)
		ret = s5k4ecgx_write(client, REG_P_PREV_MIRROR(0), 0);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_P_CAP_MIRROR(0), 0);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_G_ACTIVE_PREV_CFG, 0);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_G_PREV_OPEN_AFTER_CH, 1);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_G_NEW_CFG_SYNC, 1);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_G_PREV_CFG_CHG, 1);

	return ret;
}