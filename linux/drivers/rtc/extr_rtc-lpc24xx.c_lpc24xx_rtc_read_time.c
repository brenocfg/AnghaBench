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
typedef  int /*<<< orphan*/  u32 ;
struct rtc_time {int /*<<< orphan*/  tm_yday; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct lpc24xx_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT0_DOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CT0_HOURS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CT0_MINS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CT0_SECS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CT1_DOM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CT1_MONTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CT1_YEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CT2_DOY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC24XX_CTIME0 ; 
 int /*<<< orphan*/  LPC24XX_CTIME1 ; 
 int /*<<< orphan*/  LPC24XX_CTIME2 ; 
 struct lpc24xx_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_readl (struct lpc24xx_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc24xx_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct lpc24xx_rtc *rtc = dev_get_drvdata(dev);
	u32 ct0, ct1, ct2;

	ct0 = rtc_readl(rtc, LPC24XX_CTIME0);
	ct1 = rtc_readl(rtc, LPC24XX_CTIME1);
	ct2 = rtc_readl(rtc, LPC24XX_CTIME2);

	tm->tm_sec  = CT0_SECS(ct0);
	tm->tm_min  = CT0_MINS(ct0);
	tm->tm_hour = CT0_HOURS(ct0);
	tm->tm_wday = CT0_DOW(ct0);
	tm->tm_mon  = CT1_MONTH(ct1);
	tm->tm_mday = CT1_DOM(ct1);
	tm->tm_year = CT1_YEAR(ct1);
	tm->tm_yday = CT2_DOY(ct2);

	return 0;
}