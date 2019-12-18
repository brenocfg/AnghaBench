#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qp_entry {int dummy; } ;
struct qp_broker_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qp_broker_entry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ qp_broker_list ; 
 struct qp_entry* qp_list_get_head (TYPE_1__*) ; 
 int /*<<< orphan*/  qp_list_remove_entry (TYPE_1__*,struct qp_entry*) ; 

void vmci_qp_broker_exit(void)
{
	struct qp_entry *entry;
	struct qp_broker_entry *be;

	mutex_lock(&qp_broker_list.mutex);

	while ((entry = qp_list_get_head(&qp_broker_list))) {
		be = (struct qp_broker_entry *)entry;

		qp_list_remove_entry(&qp_broker_list, entry);
		kfree(be);
	}

	mutex_unlock(&qp_broker_list.mutex);
}