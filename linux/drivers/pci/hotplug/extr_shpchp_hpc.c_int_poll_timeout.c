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
struct timer_list {int dummy; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 struct controller* ctrl ; 
 struct controller* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_timer ; 
 int /*<<< orphan*/  shpc_isr (int /*<<< orphan*/ ,struct controller*) ; 
 int shpchp_poll_time ; 
 int /*<<< orphan*/  start_int_poll_timer (struct controller*,int) ; 

__attribute__((used)) static void int_poll_timeout(struct timer_list *t)
{
	struct controller *ctrl = from_timer(ctrl, t, poll_timer);

	/* Poll for interrupt events.  regs == NULL => polling */
	shpc_isr(0, ctrl);

	if (!shpchp_poll_time)
		shpchp_poll_time = 2; /* default polling interval is 2 sec */

	start_int_poll_timer(ctrl, shpchp_poll_time);
}