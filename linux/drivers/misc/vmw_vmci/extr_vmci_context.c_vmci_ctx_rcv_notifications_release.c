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
struct vmci_handle_arr {int dummy; } ;
struct vmci_handle {int dummy; } ;
struct vmci_ctx {int /*<<< orphan*/  lock; struct vmci_handle_arr* pending_doorbell_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx_clear_notify_call (struct vmci_ctx*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vmci_ctx* vmci_ctx_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_ctx_put (struct vmci_ctx*) ; 
 int /*<<< orphan*/  vmci_handle_arr_append_entry (struct vmci_handle_arr**,struct vmci_handle) ; 
 int /*<<< orphan*/  vmci_handle_arr_destroy (struct vmci_handle_arr*) ; 
 int /*<<< orphan*/  vmci_handle_arr_has_entry (struct vmci_handle_arr*,struct vmci_handle) ; 
 struct vmci_handle vmci_handle_arr_remove_tail (struct vmci_handle_arr*) ; 
 int /*<<< orphan*/  vmci_handle_is_invalid (struct vmci_handle) ; 

void vmci_ctx_rcv_notifications_release(u32 context_id,
					struct vmci_handle_arr *db_handle_array,
					struct vmci_handle_arr *qp_handle_array,
					bool success)
{
	struct vmci_ctx *context = vmci_ctx_get(context_id);

	spin_lock(&context->lock);
	if (!success) {
		struct vmci_handle handle;

		/*
		 * New notifications may have been added while we were not
		 * holding the context lock, so we transfer any new pending
		 * doorbell notifications to the old array, and reinstate the
		 * old array.
		 */

		handle = vmci_handle_arr_remove_tail(
					context->pending_doorbell_array);
		while (!vmci_handle_is_invalid(handle)) {
			if (!vmci_handle_arr_has_entry(db_handle_array,
						       handle)) {
				vmci_handle_arr_append_entry(
						&db_handle_array, handle);
			}
			handle = vmci_handle_arr_remove_tail(
					context->pending_doorbell_array);
		}
		vmci_handle_arr_destroy(context->pending_doorbell_array);
		context->pending_doorbell_array = db_handle_array;
		db_handle_array = NULL;
	} else {
		ctx_clear_notify_call(context);
	}
	spin_unlock(&context->lock);
	vmci_ctx_put(context);

	if (db_handle_array)
		vmci_handle_arr_destroy(db_handle_array);

	if (qp_handle_array)
		vmci_handle_arr_destroy(qp_handle_array);
}