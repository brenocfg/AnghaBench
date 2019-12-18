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
struct pxa_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTSR ; 
 int /*<<< orphan*/  RTSR_TRIG_MASK ; 
 int /*<<< orphan*/  rtc_readl (struct pxa_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_writel (struct pxa_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtsr_set_bits(struct pxa_rtc *pxa_rtc, u32 mask)
{
	u32 rtsr;

	rtsr = rtc_readl(pxa_rtc, RTSR);
	rtsr &= ~RTSR_TRIG_MASK;
	rtsr |= mask;
	rtc_writel(pxa_rtc, RTSR, rtsr);
}