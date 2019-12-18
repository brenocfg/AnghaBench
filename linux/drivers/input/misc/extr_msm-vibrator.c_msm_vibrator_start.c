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
struct msm_vibrator {int enabled; int magnitude; int /*<<< orphan*/  mutex; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  clk; TYPE_1__* input; int /*<<< orphan*/  vcc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CBCR ; 
 int /*<<< orphan*/  REG_CFG_RCGR ; 
 int /*<<< orphan*/  REG_CMD_RCGR ; 
 int /*<<< orphan*/  REG_D ; 
 int /*<<< orphan*/  REG_M ; 
 int /*<<< orphan*/  REG_N ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msm_vibrator_write (struct msm_vibrator*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_vibrator_start(struct msm_vibrator *vibrator)
{
	int d_reg_val, ret = 0;

	mutex_lock(&vibrator->mutex);

	if (!vibrator->enabled) {
		ret = clk_set_rate(vibrator->clk, 24000);
		if (ret) {
			dev_err(&vibrator->input->dev,
				"Failed to set clock rate: %d\n", ret);
			goto unlock;
		}

		ret = clk_prepare_enable(vibrator->clk);
		if (ret) {
			dev_err(&vibrator->input->dev,
				"Failed to enable clock: %d\n", ret);
			goto unlock;
		}

		ret = regulator_enable(vibrator->vcc);
		if (ret) {
			dev_err(&vibrator->input->dev,
				"Failed to enable regulator: %d\n", ret);
			clk_disable(vibrator->clk);
			goto unlock;
		}

		gpiod_set_value_cansleep(vibrator->enable_gpio, 1);

		vibrator->enabled = true;
	}

	d_reg_val = 127 - ((126 * vibrator->magnitude) / 0xffff);
	msm_vibrator_write(vibrator, REG_CFG_RCGR,
			   (2 << 12) | /* dual edge mode */
			   (0 << 8) |  /* cxo */
			   (7 << 0));
	msm_vibrator_write(vibrator, REG_M, 1);
	msm_vibrator_write(vibrator, REG_N, 128);
	msm_vibrator_write(vibrator, REG_D, d_reg_val);
	msm_vibrator_write(vibrator, REG_CMD_RCGR, 1);
	msm_vibrator_write(vibrator, REG_CBCR, 1);

unlock:
	mutex_unlock(&vibrator->mutex);

	return ret;
}