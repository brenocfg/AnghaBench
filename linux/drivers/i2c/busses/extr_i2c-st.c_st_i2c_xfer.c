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
struct st_i2c_dev {int busy; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct st_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_pm_select_idle_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_i2c_hw_config (struct st_i2c_dev*) ; 
 int st_i2c_xfer_msg (struct st_i2c_dev*,struct i2c_msg*,int,int) ; 

__attribute__((used)) static int st_i2c_xfer(struct i2c_adapter *i2c_adap,
			struct i2c_msg msgs[], int num)
{
	struct st_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	int ret, i;

	i2c_dev->busy = true;

	ret = clk_prepare_enable(i2c_dev->clk);
	if (ret) {
		dev_err(i2c_dev->dev, "Failed to prepare_enable clock\n");
		return ret;
	}

	pinctrl_pm_select_default_state(i2c_dev->dev);

	st_i2c_hw_config(i2c_dev);

	for (i = 0; (i < num) && !ret; i++)
		ret = st_i2c_xfer_msg(i2c_dev, &msgs[i], i == 0, i == num - 1);

	pinctrl_pm_select_idle_state(i2c_dev->dev);

	clk_disable_unprepare(i2c_dev->clk);

	i2c_dev->busy = false;

	return (ret < 0) ? ret : i;
}