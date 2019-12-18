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
typedef  int u32 ;
struct sam9_rtc {int events; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AT91_RTT_ALMIEN ; 
 int AT91_RTT_ALMS ; 
 int AT91_RTT_RTTINC ; 
 int AT91_RTT_RTTINCIEN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MR ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int RTC_UF ; 
 int /*<<< orphan*/  SR ; 
 int rtt_readl (struct sam9_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t at91_rtc_cache_events(struct sam9_rtc *rtc)
{
	u32 sr, mr;

	/* Shared interrupt may be for another device.  Note: reading
	 * SR clears it, so we must only read it in this irq handler!
	 */
	mr = rtt_readl(rtc, MR) & (AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN);
	sr = rtt_readl(rtc, SR) & (mr >> 16);
	if (!sr)
		return IRQ_NONE;

	/* alarm status */
	if (sr & AT91_RTT_ALMS)
		rtc->events |= (RTC_AF | RTC_IRQF);

	/* timer update/increment */
	if (sr & AT91_RTT_RTTINC)
		rtc->events |= (RTC_UF | RTC_IRQF);

	return IRQ_HANDLED;
}