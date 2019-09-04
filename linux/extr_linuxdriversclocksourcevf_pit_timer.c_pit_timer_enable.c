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

/* Variables and functions */
 scalar_t__ PITTCTRL ; 
 int PITTCTRL_TEN ; 
 int PITTCTRL_TIE ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 scalar_t__ clkevt_base ; 

__attribute__((used)) static inline void pit_timer_enable(void)
{
	__raw_writel(PITTCTRL_TEN | PITTCTRL_TIE, clkevt_base + PITTCTRL);
}