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
typedef  int u32 ;
typedef  int u16 ;
struct ina3221_data {int reg_config; int /*<<< orphan*/  pm_dev; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INA3221_CONFIG ; 
 int INA3221_CONFIG_CHx_EN (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ina3221_write_enable(struct device *dev, int channel, bool enable)
{
	struct ina3221_data *ina = dev_get_drvdata(dev);
	u16 config, mask = INA3221_CONFIG_CHx_EN(channel);
	u16 config_old = ina->reg_config & mask;
	u32 tmp;
	int ret;

	config = enable ? mask : 0;

	/* Bypass if enable status is not being changed */
	if (config_old == config)
		return 0;

	/* For enabling routine, increase refcount and resume() at first */
	if (enable) {
		ret = pm_runtime_get_sync(ina->pm_dev);
		if (ret < 0) {
			dev_err(dev, "Failed to get PM runtime\n");
			return ret;
		}
	}

	/* Enable or disable the channel */
	tmp = (ina->reg_config & ~mask) | (config & mask);
	ret = regmap_write(ina->regmap, INA3221_CONFIG, tmp);
	if (ret)
		goto fail;

	/* Cache the latest config register value */
	ina->reg_config = tmp;

	/* For disabling routine, decrease refcount or suspend() at last */
	if (!enable)
		pm_runtime_put_sync(ina->pm_dev);

	return 0;

fail:
	if (enable) {
		dev_err(dev, "Failed to enable channel %d: error %d\n",
			channel, ret);
		pm_runtime_put_sync(ina->pm_dev);
	}

	return ret;
}