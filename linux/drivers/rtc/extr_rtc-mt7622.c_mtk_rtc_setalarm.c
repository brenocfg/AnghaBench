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
struct rtc_wkalrm {struct rtc_time time; } ;
struct mtk_rtc {int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTK_AL ; 
 int /*<<< orphan*/  MTK_RTC_AL_CTL ; 
 int /*<<< orphan*/  MTK_RTC_TM_YR_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_AL_ALL ; 
 int /*<<< orphan*/  RTC_AL_EN ; 
 struct mtk_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mtk_clr (struct mtk_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_rtc_set_alarm_or_time (struct mtk_rtc*,struct rtc_time*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_rtc_setalarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct mtk_rtc *hw = dev_get_drvdata(dev);
	struct rtc_time *alrm_tm = &wkalrm->time;

	if (!MTK_RTC_TM_YR_VALID(alrm_tm->tm_year))
		return -EINVAL;

	/*
	 * Stop the alarm also implicitly including disables interrupt before
	 * setting a new one.
	 */
	mtk_clr(hw, MTK_RTC_AL_CTL, RTC_AL_EN);

	/*
	 * Avoid contention between mtk_rtc_setalarm and IRQ handler so that
	 * disabling the interrupt and awaiting for pending IRQ handler to
	 * complete.
	 */
	synchronize_irq(hw->irq);

	mtk_rtc_set_alarm_or_time(hw, alrm_tm, MTK_AL);

	/* Restart the alarm with the new setup */
	mtk_w32(hw, MTK_RTC_AL_CTL, RTC_AL_ALL);

	return 0;
}