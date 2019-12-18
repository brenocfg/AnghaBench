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
struct sh_rtc {int periodic_freq; int /*<<< orphan*/  rtc_dev; scalar_t__ regbase; } ;

/* Variables and functions */
 int PF_OXS ; 
 scalar_t__ RCR1 ; 
 unsigned int RCR1_CF ; 
 int RTC_IRQF ; 
 int RTC_UF ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int __sh_rtc_interrupt(struct sh_rtc *rtc)
{
	unsigned int tmp, pending;

	tmp = readb(rtc->regbase + RCR1);
	pending = tmp & RCR1_CF;
	tmp &= ~RCR1_CF;
	writeb(tmp, rtc->regbase + RCR1);

	/* Users have requested One x Second IRQ */
	if (pending && rtc->periodic_freq & PF_OXS)
		rtc_update_irq(rtc->rtc_dev, 1, RTC_UF | RTC_IRQF);

	return pending;
}