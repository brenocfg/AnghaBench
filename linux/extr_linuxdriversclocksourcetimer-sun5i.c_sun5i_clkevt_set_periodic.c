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
struct TYPE_2__ {int /*<<< orphan*/  ticks_per_jiffy; } ;
struct sun5i_timer_clkevt {TYPE_1__ timer; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sun5i_clkevt_time_setup (struct sun5i_timer_clkevt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun5i_clkevt_time_start (struct sun5i_timer_clkevt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun5i_clkevt_time_stop (struct sun5i_timer_clkevt*,int /*<<< orphan*/ ) ; 
 struct sun5i_timer_clkevt* to_sun5i_timer_clkevt (struct clock_event_device*) ; 

__attribute__((used)) static int sun5i_clkevt_set_periodic(struct clock_event_device *clkevt)
{
	struct sun5i_timer_clkevt *ce = to_sun5i_timer_clkevt(clkevt);

	sun5i_clkevt_time_stop(ce, 0);
	sun5i_clkevt_time_setup(ce, 0, ce->timer.ticks_per_jiffy);
	sun5i_clkevt_time_start(ce, 0, true);
	return 0;
}