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
struct sprd_rtc {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_RTC_ALARM_EN ; 
 scalar_t__ SPRD_RTC_INT_EN ; 
 int SPRD_RTC_POWEROFF_ALM_FLAG ; 
 scalar_t__ SPRD_RTC_SPG_VALUE ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_rtc_check_alarm_int(struct sprd_rtc *rtc)
{
	u32 val;
	int ret;

	ret = regmap_read(rtc->regmap, rtc->base + SPRD_RTC_SPG_VALUE, &val);
	if (ret)
		return ret;

	/*
	 * The SPRD_RTC_INT_EN register is not put in always-power-on region
	 * supplied by VDDRTC, so we should check if we need enable the alarm
	 * interrupt when system booting.
	 *
	 * If we have set SPRD_RTC_POWEROFF_ALM_FLAG which is saved in
	 * always-power-on region, that means we have set one alarm last time,
	 * so we should enable the alarm interrupt to help RTC core to see if
	 * there is an alarm already set in RTC hardware.
	 */
	if (!(val & SPRD_RTC_POWEROFF_ALM_FLAG))
		return 0;

	return regmap_update_bits(rtc->regmap, rtc->base + SPRD_RTC_INT_EN,
				  SPRD_RTC_ALARM_EN, SPRD_RTC_ALARM_EN);
}