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
struct armada38x_rtc {scalar_t__ regs_soc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_8K_ALARM2 ; 
 scalar_t__ RTC_8K_IMR ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void armada8k_unmask_interrupt(struct armada38x_rtc *rtc)
{
	writel(RTC_8K_ALARM2, rtc->regs_soc + RTC_8K_IMR);
}