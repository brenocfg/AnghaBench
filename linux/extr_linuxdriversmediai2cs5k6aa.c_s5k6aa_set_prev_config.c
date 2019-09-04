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
typedef  scalar_t__ u16 ;
struct s5k6aa_preset {int index; scalar_t__ clk_id; } ;
struct s5k6aa {scalar_t__ pclk_fmax; scalar_t__ pclk_fmin; TYPE_1__* fiv; scalar_t__ apply_cfg; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {scalar_t__ reg_fr_time; } ;

/* Variables and functions */
 scalar_t__ FR_RATE_DYNAMIC ; 
 scalar_t__ FR_RATE_Q_BEST_FRRATE ; 
 scalar_t__ FR_RATE_Q_BEST_QUALITY ; 
 int /*<<< orphan*/  REG_P_CLK_INDEX (int) ; 
 int /*<<< orphan*/  REG_P_FR_RATE_Q_TYPE (int) ; 
 int /*<<< orphan*/  REG_P_FR_RATE_TYPE (int) ; 
 int /*<<< orphan*/  REG_P_MAX_FR_TIME (int) ; 
 int /*<<< orphan*/  REG_P_MAX_OUT_RATE (int) ; 
 int /*<<< orphan*/  REG_P_MIN_FR_TIME (int) ; 
 int /*<<< orphan*/  REG_P_MIN_OUT_RATE (int) ; 
 scalar_t__ S5K6AA_MAX_HIGHRES_FR_TIME ; 
 int /*<<< orphan*/  debug ; 
 int s5k6aa_new_config_sync (struct i2c_client*,int,int) ; 
 int s5k6aa_preview_config_status (struct i2c_client*) ; 
 int s5k6aa_set_output_framefmt (struct s5k6aa*,struct s5k6aa_preset*) ; 
 int s5k6aa_write (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,scalar_t__,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5k6aa_set_prev_config(struct s5k6aa *s5k6aa,
				  struct s5k6aa_preset *preset)
{
	struct i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	int idx = preset->index;
	u16 frame_rate_q;
	int ret;

	if (s5k6aa->fiv->reg_fr_time >= S5K6AA_MAX_HIGHRES_FR_TIME)
		frame_rate_q = FR_RATE_Q_BEST_FRRATE;
	else
		frame_rate_q = FR_RATE_Q_BEST_QUALITY;

	ret = s5k6aa_set_output_framefmt(s5k6aa, preset);
	if (!ret)
		ret = s5k6aa_write(client, REG_P_MAX_OUT_RATE(idx),
				   s5k6aa->pclk_fmax);
	if (!ret)
		ret = s5k6aa_write(client, REG_P_MIN_OUT_RATE(idx),
				   s5k6aa->pclk_fmin);
	if (!ret)
		ret = s5k6aa_write(client, REG_P_CLK_INDEX(idx),
				   preset->clk_id);
	if (!ret)
		ret = s5k6aa_write(client, REG_P_FR_RATE_TYPE(idx),
				   FR_RATE_DYNAMIC);
	if (!ret)
		ret = s5k6aa_write(client, REG_P_FR_RATE_Q_TYPE(idx),
				   frame_rate_q);
	if (!ret)
		ret = s5k6aa_write(client, REG_P_MAX_FR_TIME(idx),
				   s5k6aa->fiv->reg_fr_time + 33);
	if (!ret)
		ret = s5k6aa_write(client, REG_P_MIN_FR_TIME(idx),
				   s5k6aa->fiv->reg_fr_time - 33);
	if (!ret)
		ret = s5k6aa_new_config_sync(client, 250, idx);
	if (!ret)
		ret = s5k6aa_preview_config_status(client);
	if (!ret)
		s5k6aa->apply_cfg = 0;

	v4l2_dbg(1, debug, client, "Frame interval: %d +/- 3.3ms. (%d)\n",
		 s5k6aa->fiv->reg_fr_time, ret);
	return ret;
}