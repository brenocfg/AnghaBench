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
struct tsc200x {scalar_t__ esd_timeout; int /*<<< orphan*/  esd_work; int /*<<< orphan*/  last_valid_interrupt; scalar_t__ reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc200x_start_scan (struct tsc200x*) ; 

__attribute__((used)) static void __tsc200x_enable(struct tsc200x *ts)
{
	tsc200x_start_scan(ts);

	if (ts->esd_timeout && ts->reset_gpio) {
		ts->last_valid_interrupt = jiffies;
		schedule_delayed_work(&ts->esd_work,
				round_jiffies_relative(
					msecs_to_jiffies(ts->esd_timeout)));
	}
}