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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYST_CON_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_timer_of (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_syst_clkevt_shutdown(struct clock_event_device *clkevt)
{
	/* Disable timer */
	writel(0, SYST_CON_REG(to_timer_of(clkevt)));

	return 0;
}