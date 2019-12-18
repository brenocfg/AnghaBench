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
struct speedtch_instance_data {scalar_t__ poll_delay; int /*<<< orphan*/  usbatm; int /*<<< orphan*/  status_check_timer; int /*<<< orphan*/  status_check_work; } ;

/* Variables and functions */
 scalar_t__ MAX_POLL_DELAY ; 
 int /*<<< orphan*/  atm_warn (int /*<<< orphan*/ ,char*) ; 
 struct speedtch_instance_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct speedtch_instance_data* instance ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_check_timer ; 

__attribute__((used)) static void speedtch_status_poll(struct timer_list *t)
{
	struct speedtch_instance_data *instance = from_timer(instance, t,
						             status_check_timer);

	schedule_work(&instance->status_check_work);

	/* The following check is racy, but the race is harmless */
	if (instance->poll_delay < MAX_POLL_DELAY)
		mod_timer(&instance->status_check_timer, jiffies + msecs_to_jiffies(instance->poll_delay));
	else
		atm_warn(instance->usbatm, "Too many failures - disabling line status polling\n");
}