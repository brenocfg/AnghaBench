#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  tm_wday; void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; TYPE_2__ time; } ;
struct rk808_rtc {TYPE_1__* creg; struct rk808* rk808; } ;
struct rk808 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  int_reg; int /*<<< orphan*/  alarm_seconds_reg; } ;

/* Variables and functions */
 int BIT_RTC_INTERRUPTS_REG_IT_ALARM_M ; 
 int DAYS_REG_MSK ; 
 int HOURS_REG_MSK ; 
 int MINUTES_REG_MAK ; 
 int MONTHS_REG_MSK ; 
 int NUM_ALARM_REGS ; 
 int SECONDS_REG_MSK ; 
 int YEARS_REG_MSK ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct rk808_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rockchip_to_gregorian (TYPE_2__*) ; 

__attribute__((used)) static int rk808_rtc_readalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct rk808_rtc *rk808_rtc = dev_get_drvdata(dev);
	struct rk808 *rk808 = rk808_rtc->rk808;
	u8 alrm_data[NUM_ALARM_REGS];
	uint32_t int_reg;
	int ret;

	ret = regmap_bulk_read(rk808->regmap,
			       rk808_rtc->creg->alarm_seconds_reg,
			       alrm_data, NUM_ALARM_REGS);
	if (ret) {
		dev_err(dev, "Failed to read RTC alarm date REG: %d\n", ret);
		return ret;
	}

	alrm->time.tm_sec = bcd2bin(alrm_data[0] & SECONDS_REG_MSK);
	alrm->time.tm_min = bcd2bin(alrm_data[1] & MINUTES_REG_MAK);
	alrm->time.tm_hour = bcd2bin(alrm_data[2] & HOURS_REG_MSK);
	alrm->time.tm_mday = bcd2bin(alrm_data[3] & DAYS_REG_MSK);
	alrm->time.tm_mon = (bcd2bin(alrm_data[4] & MONTHS_REG_MSK)) - 1;
	alrm->time.tm_year = (bcd2bin(alrm_data[5] & YEARS_REG_MSK)) + 100;
	rockchip_to_gregorian(&alrm->time);

	ret = regmap_read(rk808->regmap, rk808_rtc->creg->int_reg, &int_reg);
	if (ret) {
		dev_err(dev, "Failed to read RTC INT REG: %d\n", ret);
		return ret;
	}

	dev_dbg(dev, "alrm read RTC date/time %ptRd(%d) %ptRt\n",
		&alrm->time, alrm->time.tm_wday, &alrm->time);

	alrm->enabled = (int_reg & BIT_RTC_INTERRUPTS_REG_IT_ALARM_M) ? 1 : 0;

	return 0;
}