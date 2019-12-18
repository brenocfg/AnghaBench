#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time64_t ;
struct sprd_rtc {scalar_t__ base; int /*<<< orphan*/  regmap; TYPE_3__* rtc; } ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  expires; } ;
struct TYPE_5__ {int /*<<< orphan*/  enabled; TYPE_1__ node; } ;
struct TYPE_6__ {TYPE_2__ aie_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_RTC_ALARM ; 
 int /*<<< orphan*/  SPRD_RTC_ALARM_EN ; 
 scalar_t__ SPRD_RTC_INT_CLR ; 
 scalar_t__ SPRD_RTC_INT_EN ; 
 struct sprd_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rtc_time rtc_ktime_to_tm (int /*<<< orphan*/ ) ; 
 scalar_t__ rtc_tm_sub (struct rtc_time*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int sprd_rtc_lock_alarm (struct sprd_rtc*,int) ; 
 int sprd_rtc_set_aux_alarm (struct device*,struct rtc_wkalrm*) ; 
 int sprd_rtc_set_secs (struct sprd_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct sprd_rtc *rtc = dev_get_drvdata(dev);
	time64_t secs = rtc_tm_to_time64(&alrm->time);
	struct rtc_time aie_time =
		rtc_ktime_to_tm(rtc->rtc->aie_timer.node.expires);
	int ret;

	/*
	 * We have 2 groups alarms: normal alarm and auxiliary alarm. Since
	 * both normal alarm event and auxiliary alarm event can wake up system
	 * from deep sleep, but only alarm event can power up system from power
	 * down status. Moreover we do not need to poll about 125ms when
	 * updating auxiliary alarm registers. Thus we usually set auxiliary
	 * alarm when wake up system from deep sleep, and for other scenarios,
	 * we should set normal alarm with polling status.
	 *
	 * So here we check if the alarm time is set by aie_timer, if yes, we
	 * should set normal alarm, if not, we should set auxiliary alarm which
	 * means it is just a wake event.
	 */
	if (!rtc->rtc->aie_timer.enabled || rtc_tm_sub(&aie_time, &alrm->time))
		return sprd_rtc_set_aux_alarm(dev, alrm);

	/* clear the alarm interrupt status firstly */
	ret = regmap_write(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			   SPRD_RTC_ALARM_EN);
	if (ret)
		return ret;

	ret = sprd_rtc_set_secs(rtc, SPRD_RTC_ALARM, secs);
	if (ret)
		return ret;

	if (alrm->enabled) {
		ret = regmap_update_bits(rtc->regmap,
					 rtc->base + SPRD_RTC_INT_EN,
					 SPRD_RTC_ALARM_EN,
					 SPRD_RTC_ALARM_EN);
		if (ret)
			return ret;

		/* unlock the alarm to enable the alarm function. */
		ret = sprd_rtc_lock_alarm(rtc, false);
	} else {
		regmap_update_bits(rtc->regmap,
				   rtc->base + SPRD_RTC_INT_EN,
				   SPRD_RTC_ALARM_EN, 0);

		/*
		 * Lock the alarm function in case fake alarm event will power
		 * up systems.
		 */
		ret = sprd_rtc_lock_alarm(rtc, true);
	}

	return ret;
}