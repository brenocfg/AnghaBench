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
struct timer_of {int dummy; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_CTL_PERIOD_MODE ; 
 int /*<<< orphan*/  sprd_timer_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_timer_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_timer_update_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_of_base (struct timer_of*) ; 
 int /*<<< orphan*/  timer_of_period (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 

__attribute__((used)) static int sprd_timer_set_periodic(struct clock_event_device *ce)
{
	struct timer_of *to = to_timer_of(ce);

	sprd_timer_disable(timer_of_base(to));
	sprd_timer_update_counter(timer_of_base(to), timer_of_period(to));
	sprd_timer_enable(timer_of_base(to), TIMER_CTL_PERIOD_MODE);

	return 0;
}