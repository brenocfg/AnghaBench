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
struct TYPE_2__ {int maintenance_timer_expired; } ;
struct abx500_chargalg {int /*<<< orphan*/  maintenance_timer; TYPE_1__ events; } ;

/* Variables and functions */
 int FIVE_MINUTES_IN_SECONDS ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int ONE_HOUR_IN_SECONDS ; 
 int /*<<< orphan*/  hrtimer_set_expires_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void abx500_chargalg_start_maintenance_timer(struct abx500_chargalg *di,
	int duration)
{
	hrtimer_set_expires_range(&di->maintenance_timer,
		ktime_set(duration * ONE_HOUR_IN_SECONDS, 0),
		ktime_set(FIVE_MINUTES_IN_SECONDS, 0));
	di->events.maintenance_timer_expired = false;
	hrtimer_start_expires(&di->maintenance_timer, HRTIMER_MODE_REL);
}