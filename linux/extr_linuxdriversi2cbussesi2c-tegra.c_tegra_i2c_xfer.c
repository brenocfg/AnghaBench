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
struct tegra_i2c_dev {int /*<<< orphan*/  dev; } ;
struct i2c_msg {int flags; } ;
struct i2c_adapter {int dummy; } ;
typedef  enum msg_end_type { ____Placeholder_msg_end_type } msg_end_type ;

/* Variables and functions */
 int I2C_M_NOSTART ; 
 int MSG_END_CONTINUE ; 
 int MSG_END_REPEAT_START ; 
 int MSG_END_STOP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct tegra_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int tegra_i2c_xfer_msg (struct tegra_i2c_dev*,struct i2c_msg*,int) ; 

__attribute__((used)) static int tegra_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msgs[],
	int num)
{
	struct tegra_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	int i;
	int ret = 0;

	ret = pm_runtime_get_sync(i2c_dev->dev);
	if (ret < 0) {
		dev_err(i2c_dev->dev, "runtime resume failed %d\n", ret);
		return ret;
	}

	for (i = 0; i < num; i++) {
		enum msg_end_type end_type = MSG_END_STOP;

		if (i < (num - 1)) {
			if (msgs[i + 1].flags & I2C_M_NOSTART)
				end_type = MSG_END_CONTINUE;
			else
				end_type = MSG_END_REPEAT_START;
		}
		ret = tegra_i2c_xfer_msg(i2c_dev, &msgs[i], end_type);
		if (ret)
			break;
	}

	pm_runtime_put(i2c_dev->dev);

	return ret ?: i;
}