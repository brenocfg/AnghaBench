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
typedef  int /*<<< orphan*/  u32 ;
struct sdei_event {int reenable; scalar_t__ type; int /*<<< orphan*/  event_num; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ SDEI_EVENT_TYPE_SHARED ; 
 int /*<<< orphan*/  _ipi_event_disable ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sdei_api_event_disable (int /*<<< orphan*/ ) ; 
 int sdei_do_cross_call (int /*<<< orphan*/ ,struct sdei_event*) ; 
 struct sdei_event* sdei_event_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdei_events_lock ; 
 int /*<<< orphan*/  sdei_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int sdei_event_disable(u32 event_num)
{
	int err = -EINVAL;
	struct sdei_event *event;

	mutex_lock(&sdei_events_lock);
	event = sdei_event_find(event_num);
	if (!event) {
		mutex_unlock(&sdei_events_lock);
		return -ENOENT;
	}

	spin_lock(&sdei_list_lock);
	event->reenable = false;
	spin_unlock(&sdei_list_lock);

	if (event->type == SDEI_EVENT_TYPE_SHARED)
		err = sdei_api_event_disable(event->event_num);
	else
		err = sdei_do_cross_call(_ipi_event_disable, event);
	mutex_unlock(&sdei_events_lock);

	return err;
}