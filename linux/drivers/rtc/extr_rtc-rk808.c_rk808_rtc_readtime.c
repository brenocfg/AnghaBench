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
typedef  int u8 ;
struct rtc_time {void* tm_wday; void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rk808_rtc {TYPE_1__* creg; struct rk808* rk808; } ;
struct rk808 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seconds_reg; int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RTC_CTRL_REG_RTC_GET_TIME ; 
 int DAYS_REG_MSK ; 
 int HOURS_REG_MSK ; 
 int MINUTES_REG_MAK ; 
 int MONTHS_REG_MSK ; 
 int NUM_TIME_REGS ; 
 int SECONDS_REG_MSK ; 
 int WEEKS_REG_MSK ; 
 int YEARS_REG_MSK ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct rtc_time*,void*,struct rtc_time*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct rk808_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_to_gregorian (struct rtc_time*) ; 

__attribute__((used)) static int rk808_rtc_readtime(struct device *dev, struct rtc_time *tm)
{
	struct rk808_rtc *rk808_rtc = dev_get_drvdata(dev);
	struct rk808 *rk808 = rk808_rtc->rk808;
	u8 rtc_data[NUM_TIME_REGS];
	int ret;

	/* Force an update of the shadowed registers right now */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_RTC_GET_TIME,
				 BIT_RTC_CTRL_REG_RTC_GET_TIME);
	if (ret) {
		dev_err(dev, "Failed to update bits rtc_ctrl: %d\n", ret);
		return ret;
	}

	/*
	 * After we set the GET_TIME bit, the rtc time can't be read
	 * immediately. So we should wait up to 31.25 us, about one cycle of
	 * 32khz. If we clear the GET_TIME bit here, the time of i2c transfer
	 * certainly more than 31.25us: 16 * 2.5us at 400kHz bus frequency.
	 */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_RTC_GET_TIME,
				 0);
	if (ret) {
		dev_err(dev, "Failed to update bits rtc_ctrl: %d\n", ret);
		return ret;
	}

	ret = regmap_bulk_read(rk808->regmap, rk808_rtc->creg->seconds_reg,
			       rtc_data, NUM_TIME_REGS);
	if (ret) {
		dev_err(dev, "Failed to bulk read rtc_data: %d\n", ret);
		return ret;
	}

	tm->tm_sec = bcd2bin(rtc_data[0] & SECONDS_REG_MSK);
	tm->tm_min = bcd2bin(rtc_data[1] & MINUTES_REG_MAK);
	tm->tm_hour = bcd2bin(rtc_data[2] & HOURS_REG_MSK);
	tm->tm_mday = bcd2bin(rtc_data[3] & DAYS_REG_MSK);
	tm->tm_mon = (bcd2bin(rtc_data[4] & MONTHS_REG_MSK)) - 1;
	tm->tm_year = (bcd2bin(rtc_data[5] & YEARS_REG_MSK)) + 100;
	tm->tm_wday = bcd2bin(rtc_data[6] & WEEKS_REG_MSK);
	rockchip_to_gregorian(tm);
	dev_dbg(dev, "RTC date/time %ptRd(%d) %ptRt\n", tm, tm->tm_wday, tm);

	return ret;
}