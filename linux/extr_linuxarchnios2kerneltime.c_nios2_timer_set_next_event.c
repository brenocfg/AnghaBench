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
struct nios2_clockevent_dev {int /*<<< orphan*/  timer; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nios2_timer_config (int /*<<< orphan*/ *,unsigned long,int) ; 
 struct nios2_clockevent_dev* to_nios2_clkevent (struct clock_event_device*) ; 

__attribute__((used)) static int nios2_timer_set_next_event(unsigned long delta,
	struct clock_event_device *evt)
{
	struct nios2_clockevent_dev *nios2_ced = to_nios2_clkevent(evt);

	nios2_timer_config(&nios2_ced->timer, delta, false);

	return 0;
}