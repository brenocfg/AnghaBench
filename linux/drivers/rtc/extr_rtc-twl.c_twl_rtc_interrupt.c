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
typedef  int u8 ;
struct twl_rtc {scalar_t__ class; int /*<<< orphan*/  rtc; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int BIT_RTC_STATUS_REG_ALARM_M ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  REG_RTC_STATUS_REG ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_PF ; 
 int /*<<< orphan*/  TWL4030_INT_PWR_ISR1 ; 
 int /*<<< orphan*/  TWL4030_MODULE_INT ; 
 scalar_t__ TWL_4030 ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int twl_rtc_read_u8 (struct twl_rtc*,int*,int /*<<< orphan*/ ) ; 
 int twl_rtc_write_u8 (struct twl_rtc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t twl_rtc_interrupt(int irq, void *data)
{
	struct twl_rtc *twl_rtc = data;
	unsigned long events;
	int ret = IRQ_NONE;
	int res;
	u8 rd_reg;

	res = twl_rtc_read_u8(twl_rtc, &rd_reg, REG_RTC_STATUS_REG);
	if (res)
		goto out;
	/*
	 * Figure out source of interrupt: ALARM or TIMER in RTC_STATUS_REG.
	 * only one (ALARM or RTC) interrupt source may be enabled
	 * at time, we also could check our results
	 * by reading RTS_INTERRUPTS_REGISTER[IT_TIMER,IT_ALARM]
	 */
	if (rd_reg & BIT_RTC_STATUS_REG_ALARM_M)
		events = RTC_IRQF | RTC_AF;
	else
		events = RTC_IRQF | RTC_PF;

	res = twl_rtc_write_u8(twl_rtc, BIT_RTC_STATUS_REG_ALARM_M,
			       REG_RTC_STATUS_REG);
	if (res)
		goto out;

	if (twl_rtc->class == TWL_4030) {
		/* Clear on Read enabled. RTC_IT bit of TWL4030_INT_PWR_ISR1
		 * needs 2 reads to clear the interrupt. One read is done in
		 * do_twl_pwrirq(). Doing the second read, to clear
		 * the bit.
		 *
		 * FIXME the reason PWR_ISR1 needs an extra read is that
		 * RTC_IF retriggered until we cleared REG_ALARM_M above.
		 * But re-reading like this is a bad hack; by doing so we
		 * risk wrongly clearing status for some other IRQ (losing
		 * the interrupt).  Be smarter about handling RTC_UF ...
		 */
		res = twl_i2c_read_u8(TWL4030_MODULE_INT,
			&rd_reg, TWL4030_INT_PWR_ISR1);
		if (res)
			goto out;
	}

	/* Notify RTC core on event */
	rtc_update_irq(twl_rtc->rtc, 1, events);

	ret = IRQ_HANDLED;
out:
	return ret;
}