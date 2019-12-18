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
struct vmci_subscription {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int VMCI_ERROR_NOT_FOUND ; 
 int VMCI_SUCCESS ; 
 struct vmci_subscription* event_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vmci_subscription*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subscriber_mutex ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

int vmci_event_unsubscribe(u32 sub_id)
{
	struct vmci_subscription *s;

	mutex_lock(&subscriber_mutex);
	s = event_find(sub_id);
	if (s)
		list_del_rcu(&s->node);
	mutex_unlock(&subscriber_mutex);

	if (!s)
		return VMCI_ERROR_NOT_FOUND;

	synchronize_rcu();
	kfree(s);

	return VMCI_SUCCESS;
}