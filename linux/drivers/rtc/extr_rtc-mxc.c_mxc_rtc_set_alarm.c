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
struct rtc_wkalrm {int /*<<< orphan*/  enabled; int /*<<< orphan*/  time; } ;
struct rtc_time {int dummy; } ;
struct rtc_plat_data {int /*<<< orphan*/  g_rtc_alarm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_ALM_BIT ; 
 struct rtc_plat_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxc_rtc_irq_enable (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_alarm (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxc_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct rtc_plat_data *pdata = dev_get_drvdata(dev);

	rtc_update_alarm(dev, &alrm->time);

	memcpy(&pdata->g_rtc_alarm, &alrm->time, sizeof(struct rtc_time));
	mxc_rtc_irq_enable(dev, RTC_ALM_BIT, alrm->enabled);

	return 0;
}