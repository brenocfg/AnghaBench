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
 int /*<<< orphan*/  NETX_GPIO_COUNTER_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_CLOCKEVENT ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void timer_shutdown(struct clock_event_device *evt)
{
	/* disable timer */
	writel(0, NETX_GPIO_COUNTER_CTRL(TIMER_CLOCKEVENT));
}