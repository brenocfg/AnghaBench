#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vmci_handle {int /*<<< orphan*/  resource; int /*<<< orphan*/  context; } ;
struct vmci_ctx {int dummy; } ;
struct qp_broker_entry {scalar_t__ const create_id; scalar_t__ const attach_id; int /*<<< orphan*/  produce_q; int /*<<< orphan*/  state; int /*<<< orphan*/  consume_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_NOT_FOUND ; 
 int VMCI_ERROR_QUEUEPAIR_NOTATTACHED ; 
 scalar_t__ const VMCI_HOST_CONTEXT_ID ; 
 scalar_t__ const VMCI_INVALID_ID ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qp_acquire_queue_mutex (int /*<<< orphan*/ ) ; 
 struct qp_broker_entry* qp_broker_handle_to_entry (struct vmci_handle) ; 
 TYPE_1__ qp_broker_list ; 
 int /*<<< orphan*/  qp_host_unmap_queues (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_host_unregister_user_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_release_queue_mutex (int /*<<< orphan*/ ) ; 
 int qp_save_headers (struct qp_broker_entry*) ; 
 scalar_t__ vmci_ctx_get_id (struct vmci_ctx*) ; 
 int /*<<< orphan*/  vmci_ctx_qp_exists (struct vmci_ctx*,struct vmci_handle) ; 
 scalar_t__ vmci_handle_is_invalid (struct vmci_handle) ; 

int vmci_qp_broker_unmap(struct vmci_handle handle,
			 struct vmci_ctx *context,
			 u32 gid)
{
	struct qp_broker_entry *entry;
	const u32 context_id = vmci_ctx_get_id(context);
	int result;

	if (vmci_handle_is_invalid(handle) || !context ||
	    context_id == VMCI_INVALID_ID)
		return VMCI_ERROR_INVALID_ARGS;

	mutex_lock(&qp_broker_list.mutex);

	if (!vmci_ctx_qp_exists(context, handle)) {
		pr_devel("Context (ID=0x%x) not attached to queue pair (handle=0x%x:0x%x)\n",
			 context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		goto out;
	}

	entry = qp_broker_handle_to_entry(handle);
	if (!entry) {
		pr_devel("Context (ID=0x%x) reports being attached to queue pair (handle=0x%x:0x%x) that isn't present in broker\n",
			 context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		goto out;
	}

	if (context_id != entry->create_id && context_id != entry->attach_id) {
		result = VMCI_ERROR_QUEUEPAIR_NOTATTACHED;
		goto out;
	}

	if (context_id != VMCI_HOST_CONTEXT_ID) {
		qp_acquire_queue_mutex(entry->produce_q);
		result = qp_save_headers(entry);
		if (result < VMCI_SUCCESS)
			pr_warn("Failed to save queue headers for queue pair (handle=0x%x:0x%x,result=%d)\n",
				handle.context, handle.resource, result);

		qp_host_unmap_queues(gid, entry->produce_q, entry->consume_q);

		/*
		 * On hosted, when we unmap queue pairs, the VMX will also
		 * unmap the guest memory, so we invalidate the previously
		 * registered memory. If the queue pair is mapped again at a
		 * later point in time, we will need to reregister the user
		 * memory with a possibly new user VA.
		 */
		qp_host_unregister_user_memory(entry->produce_q,
					       entry->consume_q);

		/*
		 * Move state from *_MEM to *_NO_MEM.
		 */
		entry->state--;

		qp_release_queue_mutex(entry->produce_q);
	}

	result = VMCI_SUCCESS;

 out:
	mutex_unlock(&qp_broker_list.mutex);
	return result;
}