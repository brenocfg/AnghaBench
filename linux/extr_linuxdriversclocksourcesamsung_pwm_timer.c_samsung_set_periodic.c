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
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_id; scalar_t__ clock_count_per_tick; } ;

/* Variables and functions */
 TYPE_1__ pwm ; 
 int /*<<< orphan*/  samsung_time_setup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  samsung_time_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  samsung_time_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int samsung_set_periodic(struct clock_event_device *evt)
{
	samsung_time_stop(pwm.event_id);
	samsung_time_setup(pwm.event_id, pwm.clock_count_per_tick - 1);
	samsung_time_start(pwm.event_id, true);
	return 0;
}