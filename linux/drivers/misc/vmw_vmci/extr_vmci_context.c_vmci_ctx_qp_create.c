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
struct vmci_handle {int dummy; } ;
struct vmci_ctx {int /*<<< orphan*/  queue_pair_array; } ;

/* Variables and functions */
 int VMCI_ERROR_DUPLICATE_ENTRY ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int vmci_handle_arr_append_entry (int /*<<< orphan*/ *,struct vmci_handle) ; 
 int /*<<< orphan*/  vmci_handle_arr_has_entry (int /*<<< orphan*/ ,struct vmci_handle) ; 
 scalar_t__ vmci_handle_is_invalid (struct vmci_handle) ; 

int vmci_ctx_qp_create(struct vmci_ctx *context, struct vmci_handle handle)
{
	int result;

	if (context == NULL || vmci_handle_is_invalid(handle))
		return VMCI_ERROR_INVALID_ARGS;

	if (!vmci_handle_arr_has_entry(context->queue_pair_array, handle))
		result = vmci_handle_arr_append_entry(
			&context->queue_pair_array, handle);
	else
		result = VMCI_ERROR_DUPLICATE_ENTRY;

	return result;
}