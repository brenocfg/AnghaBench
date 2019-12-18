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
struct rtc_time {int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_yday; int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct rtc_wkalrm {scalar_t__ enabled; struct rtc_time time; } ;
struct lpc24xx_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC24XX_ALARM_DISABLE ; 
 int /*<<< orphan*/  LPC24XX_ALDOM ; 
 int /*<<< orphan*/  LPC24XX_ALDOW ; 
 int /*<<< orphan*/  LPC24XX_ALDOY ; 
 int /*<<< orphan*/  LPC24XX_ALHOUR ; 
 int /*<<< orphan*/  LPC24XX_ALMIN ; 
 int /*<<< orphan*/  LPC24XX_ALMON ; 
 int /*<<< orphan*/  LPC24XX_ALSEC ; 
 int /*<<< orphan*/  LPC24XX_ALYEAR ; 
 int /*<<< orphan*/  LPC24XX_AMR ; 
 struct lpc24xx_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc24xx_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc24xx_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct lpc24xx_rtc *rtc = dev_get_drvdata(dev);
	struct rtc_time *tm = &wkalrm->time;

	/* Disable alarm irq during update */
	rtc_writel(rtc, LPC24XX_AMR, LPC24XX_ALARM_DISABLE);

	rtc_writel(rtc, LPC24XX_ALSEC,  tm->tm_sec);
	rtc_writel(rtc, LPC24XX_ALMIN,  tm->tm_min);
	rtc_writel(rtc, LPC24XX_ALHOUR, tm->tm_hour);
	rtc_writel(rtc, LPC24XX_ALDOM,  tm->tm_mday);
	rtc_writel(rtc, LPC24XX_ALDOW,  tm->tm_wday);
	rtc_writel(rtc, LPC24XX_ALDOY,  tm->tm_yday);
	rtc_writel(rtc, LPC24XX_ALMON,  tm->tm_mon);
	rtc_writel(rtc, LPC24XX_ALYEAR, tm->tm_year);

	if (wkalrm->enabled)
		rtc_writel(rtc, LPC24XX_AMR, 0);

	return 0;
}