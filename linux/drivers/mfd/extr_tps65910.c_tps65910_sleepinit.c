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
struct TYPE_2__ {scalar_t__ i2chs_keepon; scalar_t__ clkout32k_keepon; scalar_t__ therm_keepon; } ;
struct tps65910_board {TYPE_1__ slp_keepon; int /*<<< orphan*/  en_dev_slp; } ;
struct tps65910 {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCTRL_DEV_SLP_MASK ; 
 int /*<<< orphan*/  SLEEP_KEEP_RES_ON_CLKOUT32K_KEEPON_MASK ; 
 int /*<<< orphan*/  SLEEP_KEEP_RES_ON_I2CHS_KEEPON_MASK ; 
 int /*<<< orphan*/  SLEEP_KEEP_RES_ON_THERM_KEEPON_MASK ; 
 int /*<<< orphan*/  TPS65910_DEVCTRL ; 
 int /*<<< orphan*/  TPS65910_SLEEP_KEEP_RES_ON ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  tps65910_reg_clear_bits (struct tps65910*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tps65910_reg_set_bits (struct tps65910*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65910_sleepinit(struct tps65910 *tps65910,
		struct tps65910_board *pmic_pdata)
{
	struct device *dev;
	int ret;

	if (!pmic_pdata->en_dev_slp)
		return 0;

	dev = tps65910->dev;

	/* enabling SLEEP device state */
	ret = tps65910_reg_set_bits(tps65910, TPS65910_DEVCTRL,
				DEVCTRL_DEV_SLP_MASK);
	if (ret < 0) {
		dev_err(dev, "set dev_slp failed: %d\n", ret);
		goto err_sleep_init;
	}

	if (pmic_pdata->slp_keepon.therm_keepon) {
		ret = tps65910_reg_set_bits(tps65910,
				TPS65910_SLEEP_KEEP_RES_ON,
				SLEEP_KEEP_RES_ON_THERM_KEEPON_MASK);
		if (ret < 0) {
			dev_err(dev, "set therm_keepon failed: %d\n", ret);
			goto disable_dev_slp;
		}
	}

	if (pmic_pdata->slp_keepon.clkout32k_keepon) {
		ret = tps65910_reg_set_bits(tps65910,
				TPS65910_SLEEP_KEEP_RES_ON,
				SLEEP_KEEP_RES_ON_CLKOUT32K_KEEPON_MASK);
		if (ret < 0) {
			dev_err(dev, "set clkout32k_keepon failed: %d\n", ret);
			goto disable_dev_slp;
		}
	}

	if (pmic_pdata->slp_keepon.i2chs_keepon) {
		ret = tps65910_reg_set_bits(tps65910,
				TPS65910_SLEEP_KEEP_RES_ON,
				SLEEP_KEEP_RES_ON_I2CHS_KEEPON_MASK);
		if (ret < 0) {
			dev_err(dev, "set i2chs_keepon failed: %d\n", ret);
			goto disable_dev_slp;
		}
	}

	return 0;

disable_dev_slp:
	tps65910_reg_clear_bits(tps65910, TPS65910_DEVCTRL,
				DEVCTRL_DEV_SLP_MASK);

err_sleep_init:
	return ret;
}