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
struct mtk_i2c {unsigned int clk_src_div; unsigned int speed_hz; unsigned int timing_reg; unsigned int high_speed_reg; unsigned int ltiming_reg; TYPE_1__* dev_comp; } ;
struct TYPE_2__ {scalar_t__ ltiming_adjust; } ;

/* Variables and functions */
 unsigned int I2C_TIME_CLR_VALUE ; 
 unsigned int I2C_TIME_DEFAULT_VALUE ; 
 unsigned int MAX_FS_MODE_SPEED ; 
 int mtk_i2c_calculate_speed (struct mtk_i2c*,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int mtk_i2c_set_speed(struct mtk_i2c *i2c, unsigned int parent_clk)
{
	unsigned int clk_src;
	unsigned int step_cnt;
	unsigned int sample_cnt;
	unsigned int l_step_cnt;
	unsigned int l_sample_cnt;
	unsigned int target_speed;
	int ret;

	clk_src = parent_clk / i2c->clk_src_div;
	target_speed = i2c->speed_hz;

	if (target_speed > MAX_FS_MODE_SPEED) {
		/* Set master code speed register */
		ret = mtk_i2c_calculate_speed(i2c, clk_src, MAX_FS_MODE_SPEED,
					      &l_step_cnt, &l_sample_cnt);
		if (ret < 0)
			return ret;

		i2c->timing_reg = (l_sample_cnt << 8) | l_step_cnt;

		/* Set the high speed mode register */
		ret = mtk_i2c_calculate_speed(i2c, clk_src, target_speed,
					      &step_cnt, &sample_cnt);
		if (ret < 0)
			return ret;

		i2c->high_speed_reg = I2C_TIME_DEFAULT_VALUE |
			(sample_cnt << 12) | (step_cnt << 8);

		if (i2c->dev_comp->ltiming_adjust)
			i2c->ltiming_reg = (l_sample_cnt << 6) | l_step_cnt |
					   (sample_cnt << 12) | (step_cnt << 9);
	} else {
		ret = mtk_i2c_calculate_speed(i2c, clk_src, target_speed,
					      &step_cnt, &sample_cnt);
		if (ret < 0)
			return ret;

		i2c->timing_reg = (sample_cnt << 8) | step_cnt;

		/* Disable the high speed transaction */
		i2c->high_speed_reg = I2C_TIME_CLR_VALUE;

		if (i2c->dev_comp->ltiming_adjust)
			i2c->ltiming_reg = (sample_cnt << 6) | step_cnt;
	}

	return 0;
}