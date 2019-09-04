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
struct kfd_process {int /*<<< orphan*/  event_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  KFD_EVENT_TYPE_HW_EXCEPTION ; 
 struct kfd_process* kfd_lookup_process_by_pasid (unsigned int) ; 
 int /*<<< orphan*/  kfd_unref_process (struct kfd_process*) ; 
 int /*<<< orphan*/  lookup_events_by_type_and_signal (struct kfd_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kfd_signal_hw_exception_event(unsigned int pasid)
{
	/*
	 * Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to exit while we are
	 * running so the lookup function increments the process ref count.
	 */
	struct kfd_process *p = kfd_lookup_process_by_pasid(pasid);

	if (!p)
		return; /* Presumably process exited. */

	mutex_lock(&p->event_mutex);

	/* Lookup events by type and signal them */
	lookup_events_by_type_and_signal(p, KFD_EVENT_TYPE_HW_EXCEPTION, NULL);

	mutex_unlock(&p->event_mutex);
	kfd_unref_process(p);
}