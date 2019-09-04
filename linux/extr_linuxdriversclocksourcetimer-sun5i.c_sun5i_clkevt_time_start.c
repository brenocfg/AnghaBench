#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ base; } ;
struct sun5i_timer_clkevt {TYPE_1__ timer; } ;

/* Variables and functions */
 int TIMER_CTL_ENABLE ; 
 int TIMER_CTL_ONESHOT ; 
 scalar_t__ TIMER_CTL_REG (int /*<<< orphan*/ ) ; 
 int TIMER_CTL_RELOAD ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sun5i_clkevt_time_start(struct sun5i_timer_clkevt *ce, u8 timer, bool periodic)
{
	u32 val = readl(ce->timer.base + TIMER_CTL_REG(timer));

	if (periodic)
		val &= ~TIMER_CTL_ONESHOT;
	else
		val |= TIMER_CTL_ONESHOT;

	writel(val | TIMER_CTL_ENABLE | TIMER_CTL_RELOAD,
	       ce->timer.base + TIMER_CTL_REG(timer));
}