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
struct sdei_event {scalar_t__ type; int /*<<< orphan*/  event_num; scalar_t__ reenable; } ;

/* Variables and functions */
 scalar_t__ SDEI_EVENT_TYPE_SHARED ; 
 int /*<<< orphan*/  _local_event_enable ; 
 int _sdei_event_register (struct sdei_event*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int sdei_api_event_enable (int /*<<< orphan*/ ) ; 
 int sdei_do_cross_call (int /*<<< orphan*/ ,struct sdei_event*) ; 
 int /*<<< orphan*/  sdei_event_destroy (struct sdei_event*) ; 
 int /*<<< orphan*/  sdei_events_lock ; 

__attribute__((used)) static int sdei_reregister_event(struct sdei_event *event)
{
	int err;

	lockdep_assert_held(&sdei_events_lock);

	err = _sdei_event_register(event);
	if (err) {
		pr_err("Failed to re-register event %u\n", event->event_num);
		sdei_event_destroy(event);
		return err;
	}

	if (event->reenable) {
		if (event->type == SDEI_EVENT_TYPE_SHARED)
			err = sdei_api_event_enable(event->event_num);
		else
			err = sdei_do_cross_call(_local_event_enable, event);
	}

	if (err)
		pr_err("Failed to re-enable event %u\n", event->event_num);

	return err;
}