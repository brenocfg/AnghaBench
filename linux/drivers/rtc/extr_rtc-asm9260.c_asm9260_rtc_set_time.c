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
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_yday; int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
struct device {int dummy; } ;
struct asm9260_rtc_priv {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ HW_DOM ; 
 scalar_t__ HW_DOW ; 
 scalar_t__ HW_DOY ; 
 scalar_t__ HW_HOUR ; 
 scalar_t__ HW_MIN ; 
 scalar_t__ HW_MONTH ; 
 scalar_t__ HW_SEC ; 
 scalar_t__ HW_YEAR ; 
 struct asm9260_rtc_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int asm9260_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct asm9260_rtc_priv *priv = dev_get_drvdata(dev);

	/*
	 * make sure SEC counter will not flip other counter on write time,
	 * real value will be written at the enf of sequence.
	 */
	iowrite32(0, priv->iobase + HW_SEC);

	iowrite32(tm->tm_year, priv->iobase + HW_YEAR);
	iowrite32(tm->tm_mon,  priv->iobase + HW_MONTH);
	iowrite32(tm->tm_mday, priv->iobase + HW_DOM);
	iowrite32(tm->tm_wday, priv->iobase + HW_DOW);
	iowrite32(tm->tm_yday, priv->iobase + HW_DOY);
	iowrite32(tm->tm_hour, priv->iobase + HW_HOUR);
	iowrite32(tm->tm_min,  priv->iobase + HW_MIN);
	iowrite32(tm->tm_sec,  priv->iobase + HW_SEC);

	return 0;
}