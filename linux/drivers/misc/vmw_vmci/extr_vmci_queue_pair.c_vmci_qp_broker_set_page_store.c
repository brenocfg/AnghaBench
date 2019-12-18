#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct vmci_handle {int /*<<< orphan*/  resource; int /*<<< orphan*/  context; } ;
struct vmci_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  resource; int /*<<< orphan*/  context; } ;
struct TYPE_5__ {TYPE_1__ handle; } ;
struct qp_broker_entry {scalar_t__ const create_id; scalar_t__ const attach_id; scalar_t__ state; int vmci_page_files; TYPE_2__ qp; int /*<<< orphan*/  consume_q; int /*<<< orphan*/  produce_q; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ VMCIQPB_ATTACHED_MEM ; 
 scalar_t__ VMCIQPB_ATTACHED_NO_MEM ; 
 scalar_t__ VMCIQPB_CREATED_MEM ; 
 scalar_t__ VMCIQPB_CREATED_NO_MEM ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_NOT_FOUND ; 
 int VMCI_ERROR_QUEUEPAIR_NOTOWNER ; 
 int VMCI_ERROR_UNAVAILABLE ; 
 scalar_t__ VMCI_HOST_CONTEXT_ID ; 
 scalar_t__ const VMCI_INVALID_ID ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qp_broker_entry* qp_broker_handle_to_entry (struct vmci_handle) ; 
 TYPE_3__ qp_broker_list ; 
 int qp_host_get_user_memory (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qp_host_map_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_host_unregister_user_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qp_notify_peer (int,struct vmci_handle,scalar_t__ const,scalar_t__) ; 
 scalar_t__ vmci_ctx_get_id (struct vmci_ctx*) ; 
 int /*<<< orphan*/  vmci_ctx_qp_exists (struct vmci_ctx*,struct vmci_handle) ; 
 scalar_t__ vmci_handle_is_invalid (struct vmci_handle) ; 

int vmci_qp_broker_set_page_store(struct vmci_handle handle,
				  u64 produce_uva,
				  u64 consume_uva,
				  struct vmci_ctx *context)
{
	struct qp_broker_entry *entry;
	int result;
	const u32 context_id = vmci_ctx_get_id(context);

	if (vmci_handle_is_invalid(handle) || !context ||
	    context_id == VMCI_INVALID_ID)
		return VMCI_ERROR_INVALID_ARGS;

	/*
	 * We only support guest to host queue pairs, so the VMX must
	 * supply UVAs for the mapped page files.
	 */

	if (produce_uva == 0 || consume_uva == 0)
		return VMCI_ERROR_INVALID_ARGS;

	mutex_lock(&qp_broker_list.mutex);

	if (!vmci_ctx_qp_exists(context, handle)) {
		pr_warn("Context (ID=0x%x) not attached to queue pair (handle=0x%x:0x%x)\n",
			context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		goto out;
	}

	entry = qp_broker_handle_to_entry(handle);
	if (!entry) {
		result = VMCI_ERROR_NOT_FOUND;
		goto out;
	}

	/*
	 * If I'm the owner then I can set the page store.
	 *
	 * Or, if a host created the queue_pair and I'm the attached peer
	 * then I can set the page store.
	 */
	if (entry->create_id != context_id &&
	    (entry->create_id != VMCI_HOST_CONTEXT_ID ||
	     entry->attach_id != context_id)) {
		result = VMCI_ERROR_QUEUEPAIR_NOTOWNER;
		goto out;
	}

	if (entry->state != VMCIQPB_CREATED_NO_MEM &&
	    entry->state != VMCIQPB_ATTACHED_NO_MEM) {
		result = VMCI_ERROR_UNAVAILABLE;
		goto out;
	}

	result = qp_host_get_user_memory(produce_uva, consume_uva,
					 entry->produce_q, entry->consume_q);
	if (result < VMCI_SUCCESS)
		goto out;

	result = qp_host_map_queues(entry->produce_q, entry->consume_q);
	if (result < VMCI_SUCCESS) {
		qp_host_unregister_user_memory(entry->produce_q,
					       entry->consume_q);
		goto out;
	}

	if (entry->state == VMCIQPB_CREATED_NO_MEM)
		entry->state = VMCIQPB_CREATED_MEM;
	else
		entry->state = VMCIQPB_ATTACHED_MEM;

	entry->vmci_page_files = true;

	if (entry->state == VMCIQPB_ATTACHED_MEM) {
		result =
		    qp_notify_peer(true, handle, context_id, entry->create_id);
		if (result < VMCI_SUCCESS) {
			pr_warn("Failed to notify peer (ID=0x%x) of attach to queue pair (handle=0x%x:0x%x)\n",
				entry->create_id, entry->qp.handle.context,
				entry->qp.handle.resource);
		}
	}

	result = VMCI_SUCCESS;
 out:
	mutex_unlock(&qp_broker_list.mutex);
	return result;
}