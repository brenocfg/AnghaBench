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
struct st_rtc {unsigned long long clkrate; int /*<<< orphan*/  alarm; } ;
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct st_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct rtc_wkalrm*,int) ; 
 unsigned long long rtc_tm_to_time64 (struct rtc_time*) ; 
 int /*<<< orphan*/  st_rtc_alarm_irq_enable (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_rtc_read_time (struct device*,struct rtc_time*) ; 
 int /*<<< orphan*/  st_rtc_set_hw_alarm (struct st_rtc*,unsigned long long,unsigned long long) ; 

__attribute__((used)) static int st_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct st_rtc *rtc = dev_get_drvdata(dev);
	struct rtc_time now;
	unsigned long long now_secs;
	unsigned long long alarm_secs;
	unsigned long long lpa;

	st_rtc_read_time(dev, &now);
	now_secs = rtc_tm_to_time64(&now);
	alarm_secs = rtc_tm_to_time64(&t->time);

	memcpy(&rtc->alarm, t, sizeof(struct rtc_wkalrm));

	/* Now many secs to fire */
	alarm_secs -= now_secs;
	lpa = (unsigned long long)alarm_secs * rtc->clkrate;

	st_rtc_set_hw_alarm(rtc, lpa >> 32, lpa);
	st_rtc_alarm_irq_enable(dev, t->enabled);

	return 0;
}