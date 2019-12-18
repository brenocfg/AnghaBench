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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_time {scalar_t__ tm_wday; scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
struct rk808_rtc {TYPE_1__* creg; struct rk808* rk808; } ;
struct rk808 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_reg; int /*<<< orphan*/  seconds_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RTC_CTRL_REG_STOP_RTC_M ; 
 int NUM_TIME_REGS ; 
 int /*<<< orphan*/  bin2bcd (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct rtc_time*,scalar_t__,struct rtc_time*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct rk808_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gregorian_to_rockchip (struct rtc_time*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk808_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct rk808_rtc *rk808_rtc = dev_get_drvdata(dev);
	struct rk808 *rk808 = rk808_rtc->rk808;
	u8 rtc_data[NUM_TIME_REGS];
	int ret;

	dev_dbg(dev, "set RTC date/time %ptRd(%d) %ptRt\n", tm, tm->tm_wday, tm);
	gregorian_to_rockchip(tm);
	rtc_data[0] = bin2bcd(tm->tm_sec);
	rtc_data[1] = bin2bcd(tm->tm_min);
	rtc_data[2] = bin2bcd(tm->tm_hour);
	rtc_data[3] = bin2bcd(tm->tm_mday);
	rtc_data[4] = bin2bcd(tm->tm_mon + 1);
	rtc_data[5] = bin2bcd(tm->tm_year - 100);
	rtc_data[6] = bin2bcd(tm->tm_wday);

	/* Stop RTC while updating the RTC registers */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_STOP_RTC_M,
				 BIT_RTC_CTRL_REG_STOP_RTC_M);
	if (ret) {
		dev_err(dev, "Failed to update RTC control: %d\n", ret);
		return ret;
	}

	ret = regmap_bulk_write(rk808->regmap, rk808_rtc->creg->seconds_reg,
				rtc_data, NUM_TIME_REGS);
	if (ret) {
		dev_err(dev, "Failed to bull write rtc_data: %d\n", ret);
		return ret;
	}
	/* Start RTC again */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_STOP_RTC_M, 0);
	if (ret) {
		dev_err(dev, "Failed to update RTC control: %d\n", ret);
		return ret;
	}
	return 0;
}