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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ base; } ;
struct sun5i_timer_clkevt {TYPE_1__ timer; } ;

/* Variables and functions */
 scalar_t__ TIMER_INTVAL_LO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun5i_clkevt_time_setup(struct sun5i_timer_clkevt *ce, u8 timer, u32 delay)
{
	writel(delay, ce->timer.base + TIMER_INTVAL_LO_REG(timer));
}