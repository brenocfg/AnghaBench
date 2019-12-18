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
struct lpc24xx_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC24XX_ALARM_DISABLE ; 
 int /*<<< orphan*/  LPC24XX_AMR ; 
 struct lpc24xx_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc24xx_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc24xx_rtc_alarm_irq_enable(struct device *dev, unsigned int enable)
{
	struct lpc24xx_rtc *rtc = dev_get_drvdata(dev);

	if (enable)
		rtc_writel(rtc, LPC24XX_AMR, 0);
	else
		rtc_writel(rtc, LPC24XX_AMR, LPC24XX_ALARM_DISABLE);

	return 0;
}