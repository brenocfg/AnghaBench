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
typedef  int /*<<< orphan*/  vmci_event_release_cb ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vmci_queue {int dummy; } ;
struct vmci_handle {int dummy; } ;
struct vmci_ctx {int dummy; } ;
struct qp_broker_entry {int /*<<< orphan*/  resource; struct vmci_queue* consume_q; struct vmci_queue* produce_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_HOST_CONTEXT_ID ; 
 struct vmci_handle VMCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  VMCI_INVALID_ID ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  pr_devel (char*,int) ; 
 int qp_broker_alloc (struct vmci_handle,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vmci_ctx*,int /*<<< orphan*/ ,void*,struct qp_broker_entry**,int*) ; 
 struct vmci_ctx* vmci_ctx_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_ctx_put (struct vmci_ctx*) ; 
 scalar_t__ vmci_handle_is_invalid (struct vmci_handle) ; 
 struct vmci_handle vmci_make_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmci_handle vmci_resource_handle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qp_alloc_host_work(struct vmci_handle *handle,
			      struct vmci_queue **produce_q,
			      u64 produce_size,
			      struct vmci_queue **consume_q,
			      u64 consume_size,
			      u32 peer,
			      u32 flags,
			      u32 priv_flags,
			      vmci_event_release_cb wakeup_cb,
			      void *client_data)
{
	struct vmci_handle new_handle;
	struct vmci_ctx *context;
	struct qp_broker_entry *entry;
	int result;
	bool swap;

	if (vmci_handle_is_invalid(*handle)) {
		new_handle = vmci_make_handle(
			VMCI_HOST_CONTEXT_ID, VMCI_INVALID_ID);
	} else
		new_handle = *handle;

	context = vmci_ctx_get(VMCI_HOST_CONTEXT_ID);
	entry = NULL;
	result =
	    qp_broker_alloc(new_handle, peer, flags, priv_flags,
			    produce_size, consume_size, NULL, context,
			    wakeup_cb, client_data, &entry, &swap);
	if (result == VMCI_SUCCESS) {
		if (swap) {
			/*
			 * If this is a local queue pair, the attacher
			 * will swap around produce and consume
			 * queues.
			 */

			*produce_q = entry->consume_q;
			*consume_q = entry->produce_q;
		} else {
			*produce_q = entry->produce_q;
			*consume_q = entry->consume_q;
		}

		*handle = vmci_resource_handle(&entry->resource);
	} else {
		*handle = VMCI_INVALID_HANDLE;
		pr_devel("queue pair broker failed to alloc (result=%d)\n",
			 result);
	}
	vmci_ctx_put(context);
	return result;
}