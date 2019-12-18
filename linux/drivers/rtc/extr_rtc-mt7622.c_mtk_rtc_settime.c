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
struct rtc_time {int /*<<< orphan*/  tm_year; } ;
struct mtk_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTK_RTC_CTL ; 
 int /*<<< orphan*/  MTK_RTC_TM_YR_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_TC ; 
 int /*<<< orphan*/  RTC_RC_STOP ; 
 struct mtk_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mtk_clr (struct mtk_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_rtc_set_alarm_or_time (struct mtk_rtc*,struct rtc_time*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_set (struct mtk_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_rtc_settime(struct device *dev, struct rtc_time *tm)
{
	struct mtk_rtc *hw = dev_get_drvdata(dev);

	if (!MTK_RTC_TM_YR_VALID(tm->tm_year))
		return -EINVAL;

	/* Stop time counter before setting a new one*/
	mtk_set(hw, MTK_RTC_CTL, RTC_RC_STOP);

	mtk_rtc_set_alarm_or_time(hw, tm, MTK_TC);

	/* Restart the time counter */
	mtk_clr(hw, MTK_RTC_CTL, RTC_RC_STOP);

	return 0;
}