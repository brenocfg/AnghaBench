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
struct qp_guest_endpoint {int dummy; } ;
struct qp_entry {int flags; scalar_t__ ref_count; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int VMCI_QPFLAG_LOCAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qp_detatch_hypercall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_guest_endpoint_destroy (struct qp_guest_endpoint*) ; 
 TYPE_1__ qp_guest_endpoints ; 
 struct qp_entry* qp_list_get_head (TYPE_1__*) ; 
 int /*<<< orphan*/  qp_list_remove_entry (TYPE_1__*,struct qp_entry*) ; 

void vmci_qp_guest_endpoints_exit(void)
{
	struct qp_entry *entry;
	struct qp_guest_endpoint *ep;

	mutex_lock(&qp_guest_endpoints.mutex);

	while ((entry = qp_list_get_head(&qp_guest_endpoints))) {
		ep = (struct qp_guest_endpoint *)entry;

		/* Don't make a hypercall for local queue_pairs. */
		if (!(entry->flags & VMCI_QPFLAG_LOCAL))
			qp_detatch_hypercall(entry->handle);

		/* We cannot fail the exit, so let's reset ref_count. */
		entry->ref_count = 0;
		qp_list_remove_entry(&qp_guest_endpoints, entry);

		qp_guest_endpoint_destroy(ep);
	}

	mutex_unlock(&qp_guest_endpoints.mutex);
}