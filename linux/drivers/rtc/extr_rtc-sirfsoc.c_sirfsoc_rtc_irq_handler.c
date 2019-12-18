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
struct sirfsoc_rtc_drv {int /*<<< orphan*/  rtc; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 int /*<<< orphan*/  RTC_STATUS ; 
 unsigned long SIRFSOC_RTC_AL0 ; 
 unsigned long SIRFSOC_RTC_AL0E ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 
 unsigned long sirfsoc_rtc_readl (struct sirfsoc_rtc_drv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sirfsoc_rtc_writel (struct sirfsoc_rtc_drv*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sirfsoc_rtc_irq_handler(int irq, void *pdata)
{
	struct sirfsoc_rtc_drv *rtcdrv = pdata;
	unsigned long rtc_status_reg = 0x0;
	unsigned long events = 0x0;

	spin_lock(&rtcdrv->lock);

	rtc_status_reg = sirfsoc_rtc_readl(rtcdrv, RTC_STATUS);
	/* this bit will be set ONLY if an alarm was active
	 * and it expired NOW
	 * So this is being used as an ASSERT
	 */
	if (rtc_status_reg & SIRFSOC_RTC_AL0) {
		/*
		 * clear the RTC status register's alarm bit
		 * mask out the lower status bits
		 */
		rtc_status_reg &= ~0x07;
		/* write 1 into SIRFSOC_RTC_AL0 to ACK the alarm interrupt */
		rtc_status_reg |= (SIRFSOC_RTC_AL0);
		/* Clear the Alarm enable bit */
		rtc_status_reg &= ~(SIRFSOC_RTC_AL0E);
	}

	sirfsoc_rtc_writel(rtcdrv, RTC_STATUS, rtc_status_reg);

	spin_unlock(&rtcdrv->lock);

	/* this should wake up any apps polling/waiting on the read
	 * after setting the alarm
	 */
	events |= RTC_IRQF | RTC_AF;
	rtc_update_irq(rtcdrv->rtc, 1, events);

	return IRQ_HANDLED;
}