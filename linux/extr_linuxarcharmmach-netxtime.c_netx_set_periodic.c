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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETX_GPIO_COUNTER_CTRL (int /*<<< orphan*/ ) ; 
 int NETX_GPIO_COUNTER_CTRL_IRQ_EN ; 
 int NETX_GPIO_COUNTER_CTRL_RST_EN ; 
 int NETX_GPIO_COUNTER_CTRL_RUN ; 
 int /*<<< orphan*/  NETX_GPIO_COUNTER_MAX (int /*<<< orphan*/ ) ; 
 int NETX_LATCH ; 
 int /*<<< orphan*/  TIMER_CLOCKEVENT ; 
 int /*<<< orphan*/  timer_shutdown (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netx_set_periodic(struct clock_event_device *evt)
{
	u32 tmode = NETX_GPIO_COUNTER_CTRL_RST_EN |
		    NETX_GPIO_COUNTER_CTRL_IRQ_EN | NETX_GPIO_COUNTER_CTRL_RUN;

	timer_shutdown(evt);
	writel(NETX_LATCH, NETX_GPIO_COUNTER_MAX(TIMER_CLOCKEVENT));
	writel(tmode, NETX_GPIO_COUNTER_CTRL(TIMER_CLOCKEVENT));

	return 0;
}