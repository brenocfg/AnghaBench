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
struct sdei_event {scalar_t__ type; int /*<<< orphan*/  private_registered; struct sdei_event* registered; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ SDEI_EVENT_TYPE_SHARED ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sdei_event*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdei_events_lock ; 
 int /*<<< orphan*/  sdei_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdei_event_destroy(struct sdei_event *event)
{
	lockdep_assert_held(&sdei_events_lock);

	spin_lock(&sdei_list_lock);
	list_del(&event->list);
	spin_unlock(&sdei_list_lock);

	if (event->type == SDEI_EVENT_TYPE_SHARED)
		kfree(event->registered);
	else
		free_percpu(event->private_registered);

	kfree(event);
}