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
typedef  int u16 ;
struct tps65910 {int /*<<< orphan*/  regmap; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_COMP_REGS ; 
 int /*<<< orphan*/  TPS65910_RTC_COMP_LSB ; 
 int /*<<< orphan*/  TPS65910_RTC_CTRL ; 
 int /*<<< orphan*/  TPS65910_RTC_CTRL_AUTO_COMP ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tps65910* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65910_rtc_set_calibration(struct device *dev, int calibration)
{
	unsigned char comp_data[NUM_COMP_REGS];
	struct tps65910 *tps = dev_get_drvdata(dev->parent);
	s16 value;
	int ret;

	/*
	 * TPS65910 uses two's complement 16 bit value for compensation for RTC
	 * crystal inaccuracies. One time every hour when seconds counter
	 * increments from 0 to 1 compensation value will be added to internal
	 * RTC counter value.
	 *
	 * Compensation value 0x7FFF is prohibited value.
	 *
	 * Valid range for compensation value: [-32768 .. 32766]
	 */
	if ((calibration < -32768) || (calibration > 32766)) {
		dev_err(dev, "RTC calibration value out of range: %d\n",
			calibration);
		return -EINVAL;
	}

	value = (s16)calibration;

	comp_data[0] = (u16)value & 0xFF;
	comp_data[1] = ((u16)value >> 8) & 0xFF;

	/* Update all the compensation registers in one shot */
	ret = regmap_bulk_write(tps->regmap, TPS65910_RTC_COMP_LSB,
		comp_data, NUM_COMP_REGS);
	if (ret < 0) {
		dev_err(dev, "rtc_set_calibration error: %d\n", ret);
		return ret;
	}

	/* Enable automatic compensation */
	ret = regmap_update_bits(tps->regmap, TPS65910_RTC_CTRL,
		TPS65910_RTC_CTRL_AUTO_COMP, TPS65910_RTC_CTRL_AUTO_COMP);
	if (ret < 0)
		dev_err(dev, "auto_comp enable failed with error: %d\n", ret);

	return ret;
}