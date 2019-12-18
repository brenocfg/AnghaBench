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
typedef  scalar_t__ u32 ;
struct vmci_handle_arr {int dummy; } ;
struct vmci_handle {int dummy; } ;
struct vmci_ctx {int /*<<< orphan*/  lock; struct vmci_handle_arr* pending_doorbell_array; struct vmci_handle_arr* doorbell_array; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_NOT_FOUND ; 
 scalar_t__ VMCI_INVALID_ID ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vmci_ctx* vmci_ctx_get (scalar_t__) ; 
 int /*<<< orphan*/  vmci_ctx_put (struct vmci_ctx*) ; 
 struct vmci_handle vmci_handle_arr_remove_tail (struct vmci_handle_arr*) ; 
 int /*<<< orphan*/  vmci_handle_is_invalid (struct vmci_handle) ; 

int vmci_ctx_dbell_destroy_all(u32 context_id)
{
	struct vmci_ctx *context;
	struct vmci_handle handle;

	if (context_id == VMCI_INVALID_ID)
		return VMCI_ERROR_INVALID_ARGS;

	context = vmci_ctx_get(context_id);
	if (context == NULL)
		return VMCI_ERROR_NOT_FOUND;

	spin_lock(&context->lock);
	do {
		struct vmci_handle_arr *arr = context->doorbell_array;
		handle = vmci_handle_arr_remove_tail(arr);
	} while (!vmci_handle_is_invalid(handle));
	do {
		struct vmci_handle_arr *arr = context->pending_doorbell_array;
		handle = vmci_handle_arr_remove_tail(arr);
	} while (!vmci_handle_is_invalid(handle));
	spin_unlock(&context->lock);

	vmci_ctx_put(context);

	return VMCI_SUCCESS;
}