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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct vmci_qp_page_store {int /*<<< orphan*/  len; int /*<<< orphan*/  pages; } ;
struct vmci_handle {int /*<<< orphan*/  resource; int /*<<< orphan*/  context; } ;
struct vmci_ctx {int dummy; } ;
struct qp_broker_entry {scalar_t__ const create_id; scalar_t__ const attach_id; int /*<<< orphan*/  client_data; int /*<<< orphan*/  (* wakeup_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  state; int /*<<< orphan*/  produce_q; int /*<<< orphan*/  consume_q; int /*<<< orphan*/  qp; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  QPE_NUM_PAGES (int /*<<< orphan*/ ) ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_NOT_FOUND ; 
 int VMCI_ERROR_QUEUEPAIR_NOTATTACHED ; 
 scalar_t__ const VMCI_HOST_CONTEXT_ID ; 
 scalar_t__ const VMCI_INVALID_ID ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_acquire_queue_mutex (int /*<<< orphan*/ ) ; 
 struct qp_broker_entry* qp_broker_handle_to_entry (struct vmci_handle) ; 
 TYPE_1__ qp_broker_list ; 
 int qp_host_register_user_memory (struct vmci_qp_page_store*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_release_queue_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_reset_saved_headers (struct qp_broker_entry*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ vmci_ctx_get_id (struct vmci_ctx*) ; 
 int /*<<< orphan*/  vmci_ctx_qp_exists (struct vmci_ctx*,struct vmci_handle) ; 
 scalar_t__ vmci_handle_is_invalid (struct vmci_handle) ; 

int vmci_qp_broker_map(struct vmci_handle handle,
		       struct vmci_ctx *context,
		       u64 guest_mem)
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

	result = VMCI_SUCCESS;

	if (context_id != VMCI_HOST_CONTEXT_ID) {
		struct vmci_qp_page_store page_store;

		page_store.pages = guest_mem;
		page_store.len = QPE_NUM_PAGES(entry->qp);

		qp_acquire_queue_mutex(entry->produce_q);
		qp_reset_saved_headers(entry);
		result =
		    qp_host_register_user_memory(&page_store,
						 entry->produce_q,
						 entry->consume_q);
		qp_release_queue_mutex(entry->produce_q);
		if (result == VMCI_SUCCESS) {
			/* Move state from *_NO_MEM to *_MEM */

			entry->state++;

			if (entry->wakeup_cb)
				entry->wakeup_cb(entry->client_data);
		}
	}

 out:
	mutex_unlock(&qp_broker_list.mutex);
	return result;
}