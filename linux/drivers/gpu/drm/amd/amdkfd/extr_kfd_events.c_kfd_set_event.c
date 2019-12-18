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
typedef  int /*<<< orphan*/  uint32_t ;
struct kfd_process {int /*<<< orphan*/  event_mutex; } ;
struct kfd_event {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ event_can_be_cpu_signaled (struct kfd_event*) ; 
 struct kfd_event* lookup_event_by_id (struct kfd_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_event (struct kfd_event*) ; 

int kfd_set_event(struct kfd_process *p, uint32_t event_id)
{
	int ret = 0;
	struct kfd_event *ev;

	mutex_lock(&p->event_mutex);

	ev = lookup_event_by_id(p, event_id);

	if (ev && event_can_be_cpu_signaled(ev))
		set_event(ev);
	else
		ret = -EINVAL;

	mutex_unlock(&p->event_mutex);
	return ret;
}