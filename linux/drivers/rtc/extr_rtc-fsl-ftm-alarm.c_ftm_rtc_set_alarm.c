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
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {struct rtc_time time; } ;
struct ftm_rtc {unsigned long alarm_freq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  FTM_MOD ; 
 unsigned long MAX_COUNT_VAL ; 
 struct ftm_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ftm_clean_alarm (struct ftm_rtc*) ; 
 int /*<<< orphan*/  ftm_counter_enable (struct ftm_rtc*) ; 
 int /*<<< orphan*/  ftm_irq_disable (struct ftm_rtc*) ; 
 int /*<<< orphan*/  ftm_irq_enable (struct ftm_rtc*) ; 
 int /*<<< orphan*/  ftm_rtc_read_time (struct device*,struct rtc_time*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  rtc_writel (struct ftm_rtc*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ftm_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	struct rtc_time tm;
	unsigned long now, alm_time, cycle;
	struct ftm_rtc *rtc = dev_get_drvdata(dev);

	ftm_rtc_read_time(dev, &tm);
	rtc_tm_to_time(&tm, &now);
	rtc_tm_to_time(&alm->time, &alm_time);

	ftm_clean_alarm(rtc);
	cycle = (alm_time - now) * rtc->alarm_freq;
	if (cycle > MAX_COUNT_VAL) {
		pr_err("Out of alarm range {0~262} seconds.\n");
		return -ERANGE;
	}

	ftm_irq_disable(rtc);

	/*
	 * The counter increments until the value of MOD is reached,
	 * at which point the counter is reloaded with the value of CNTIN.
	 * The TOF (the overflow flag) bit is set when the FTM counter
	 * changes from MOD to CNTIN. So we should using the cycle - 1.
	 */
	rtc_writel(rtc, FTM_MOD, cycle - 1);

	ftm_counter_enable(rtc);
	ftm_irq_enable(rtc);

	return 0;

}