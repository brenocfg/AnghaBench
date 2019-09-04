#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct clock_event_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ (* read ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int ETIME ; 
 int MIN_OSCR_DELTA ; 
 scalar_t__ TIMER_AS_VAL ; 
 scalar_t__ TIMER_IER_VAL ; 
 scalar_t__ TIMER_MATCH_VAL ; 
 int TIMER_MATCH_W_ACTIVE ; 
 TYPE_1__ clocksource ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int msecs_to_loops (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ regbase ; 
 scalar_t__ stub1 (TYPE_1__*) ; 
 scalar_t__ stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int vt8500_timer_set_next_event(unsigned long cycles,
				    struct clock_event_device *evt)
{
	int loops = msecs_to_loops(10);
	u64 alarm = clocksource.read(&clocksource) + cycles;
	while ((readl(regbase + TIMER_AS_VAL) & TIMER_MATCH_W_ACTIVE)
						&& --loops)
		cpu_relax();
	writel((unsigned long)alarm, regbase + TIMER_MATCH_VAL);

	if ((signed)(alarm - clocksource.read(&clocksource)) <= MIN_OSCR_DELTA)
		return -ETIME;

	writel(1, regbase + TIMER_IER_VAL);

	return 0;
}