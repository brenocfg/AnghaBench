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
struct rtc_time {int tm_year; int tm_mon; unsigned char tm_mday; unsigned char tm_hour; unsigned char tm_min; unsigned char tm_sec; } ;
struct ds1286_priv {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTC_CMD ; 
 int /*<<< orphan*/  RTC_DATE ; 
 int /*<<< orphan*/  RTC_HOURS ; 
 int /*<<< orphan*/  RTC_HUNDREDTH_SECOND ; 
 int /*<<< orphan*/  RTC_MINUTES ; 
 int /*<<< orphan*/  RTC_MONTH ; 
 int /*<<< orphan*/  RTC_SECONDS ; 
 unsigned char RTC_TE ; 
 int /*<<< orphan*/  RTC_YEAR ; 
 void* bin2bcd (unsigned int) ; 
 struct ds1286_priv* dev_get_drvdata (struct device*) ; 
 unsigned char ds1286_rtc_read (struct ds1286_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1286_rtc_write (struct ds1286_priv*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ds1286_set_time(struct device *dev, struct rtc_time *tm)
{
	struct ds1286_priv *priv = dev_get_drvdata(dev);
	unsigned char mon, day, hrs, min, sec;
	unsigned char save_control;
	unsigned int yrs;
	unsigned long flags;

	yrs = tm->tm_year + 1900;
	mon = tm->tm_mon + 1;   /* tm_mon starts at zero */
	day = tm->tm_mday;
	hrs = tm->tm_hour;
	min = tm->tm_min;
	sec = tm->tm_sec;

	if (yrs < 1970)
		return -EINVAL;

	yrs -= 1940;
	if (yrs > 255)    /* They are unsigned */
		return -EINVAL;

	if (yrs >= 100)
		yrs -= 100;

	sec = bin2bcd(sec);
	min = bin2bcd(min);
	hrs = bin2bcd(hrs);
	day = bin2bcd(day);
	mon = bin2bcd(mon);
	yrs = bin2bcd(yrs);

	spin_lock_irqsave(&priv->lock, flags);
	save_control = ds1286_rtc_read(priv, RTC_CMD);
	ds1286_rtc_write(priv, (save_control|RTC_TE), RTC_CMD);

	ds1286_rtc_write(priv, yrs, RTC_YEAR);
	ds1286_rtc_write(priv, mon, RTC_MONTH);
	ds1286_rtc_write(priv, day, RTC_DATE);
	ds1286_rtc_write(priv, hrs, RTC_HOURS);
	ds1286_rtc_write(priv, min, RTC_MINUTES);
	ds1286_rtc_write(priv, sec, RTC_SECONDS);
	ds1286_rtc_write(priv, 0, RTC_HUNDREDTH_SECOND);

	ds1286_rtc_write(priv, save_control, RTC_CMD);
	spin_unlock_irqrestore(&priv->lock, flags);
	return 0;
}