#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vmci_handle {int dummy; } ;
struct TYPE_5__ {int flags; int ref_count; } ;
struct qp_guest_endpoint {TYPE_2__ qp; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int VMCI_ERROR_NOT_FOUND ; 
 int VMCI_QPFLAG_LOCAL ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qp_detatch_hypercall (struct vmci_handle) ; 
 int /*<<< orphan*/  qp_guest_endpoint_destroy (struct qp_guest_endpoint*) ; 
 TYPE_1__ qp_guest_endpoints ; 
 struct qp_guest_endpoint* qp_guest_handle_to_entry (struct vmci_handle) ; 
 int /*<<< orphan*/  qp_list_remove_entry (TYPE_1__*,TYPE_2__*) ; 
 int qp_notify_peer_local (int,struct vmci_handle) ; 

__attribute__((used)) static int qp_detatch_guest_work(struct vmci_handle handle)
{
	int result;
	struct qp_guest_endpoint *entry;
	u32 ref_count = ~0;	/* To avoid compiler warning below */

	mutex_lock(&qp_guest_endpoints.mutex);

	entry = qp_guest_handle_to_entry(handle);
	if (!entry) {
		mutex_unlock(&qp_guest_endpoints.mutex);
		return VMCI_ERROR_NOT_FOUND;
	}

	if (entry->qp.flags & VMCI_QPFLAG_LOCAL) {
		result = VMCI_SUCCESS;

		if (entry->qp.ref_count > 1) {
			result = qp_notify_peer_local(false, handle);
			/*
			 * We can fail to notify a local queuepair
			 * because we can't allocate.  We still want
			 * to release the entry if that happens, so
			 * don't bail out yet.
			 */
		}
	} else {
		result = qp_detatch_hypercall(handle);
		if (result < VMCI_SUCCESS) {
			/*
			 * We failed to notify a non-local queuepair.
			 * That other queuepair might still be
			 * accessing the shared memory, so don't
			 * release the entry yet.  It will get cleaned
			 * up by VMCIqueue_pair_Exit() if necessary
			 * (assuming we are going away, otherwise why
			 * did this fail?).
			 */

			mutex_unlock(&qp_guest_endpoints.mutex);
			return result;
		}
	}

	/*
	 * If we get here then we either failed to notify a local queuepair, or
	 * we succeeded in all cases.  Release the entry if required.
	 */

	entry->qp.ref_count--;
	if (entry->qp.ref_count == 0)
		qp_list_remove_entry(&qp_guest_endpoints, &entry->qp);

	/* If we didn't remove the entry, this could change once we unlock. */
	if (entry)
		ref_count = entry->qp.ref_count;

	mutex_unlock(&qp_guest_endpoints.mutex);

	if (ref_count == 0)
		qp_guest_endpoint_destroy(entry);

	return result;
}