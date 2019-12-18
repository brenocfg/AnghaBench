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
struct vmci_handle {scalar_t__ context; int /*<<< orphan*/  resource; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait_queue; } ;
struct vmci_ctx {int /*<<< orphan*/  lock; TYPE_1__ host_context; int /*<<< orphan*/  pending_doorbell_array; int /*<<< orphan*/  doorbell_array; } ;

/* Variables and functions */
 scalar_t__ VMCI_CONTEXT_IS_VM (scalar_t__) ; 
 int VMCI_ERROR_DST_UNREACHABLE ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_NOT_FOUND ; 
 int VMCI_ERROR_NO_ACCESS ; 
 scalar_t__ VMCI_HOST_CONTEXT_ID ; 
 scalar_t__ VMCI_NO_PRIVILEGE_FLAGS ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  ctx_signal_notify (struct vmci_ctx*) ; 
 int /*<<< orphan*/  pr_devel (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vmci_context_get_priv_flags (scalar_t__) ; 
 struct vmci_ctx* vmci_ctx_get (scalar_t__) ; 
 int /*<<< orphan*/  vmci_ctx_put (struct vmci_ctx*) ; 
 int vmci_dbell_get_priv_flags (struct vmci_handle,scalar_t__*) ; 
 int vmci_dbell_host_context_notify (scalar_t__,struct vmci_handle) ; 
 scalar_t__ vmci_deny_interaction (scalar_t__,scalar_t__) ; 
 int vmci_handle_arr_append_entry (int /*<<< orphan*/ *,struct vmci_handle) ; 
 int /*<<< orphan*/  vmci_handle_arr_has_entry (int /*<<< orphan*/ ,struct vmci_handle) ; 
 scalar_t__ vmci_handle_is_invalid (struct vmci_handle) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int vmci_ctx_notify_dbell(u32 src_cid,
			  struct vmci_handle handle,
			  u32 src_priv_flags)
{
	struct vmci_ctx *dst_context;
	int result;

	if (vmci_handle_is_invalid(handle))
		return VMCI_ERROR_INVALID_ARGS;

	/* Get the target VM's VMCI context. */
	dst_context = vmci_ctx_get(handle.context);
	if (!dst_context) {
		pr_devel("Invalid context (ID=0x%x)\n", handle.context);
		return VMCI_ERROR_NOT_FOUND;
	}

	if (src_cid != handle.context) {
		u32 dst_priv_flags;

		if (VMCI_CONTEXT_IS_VM(src_cid) &&
		    VMCI_CONTEXT_IS_VM(handle.context)) {
			pr_devel("Doorbell notification from VM to VM not supported (src=0x%x, dst=0x%x)\n",
				 src_cid, handle.context);
			result = VMCI_ERROR_DST_UNREACHABLE;
			goto out;
		}

		result = vmci_dbell_get_priv_flags(handle, &dst_priv_flags);
		if (result < VMCI_SUCCESS) {
			pr_warn("Failed to get privilege flags for destination (handle=0x%x:0x%x)\n",
				handle.context, handle.resource);
			goto out;
		}

		if (src_cid != VMCI_HOST_CONTEXT_ID ||
		    src_priv_flags == VMCI_NO_PRIVILEGE_FLAGS) {
			src_priv_flags = vmci_context_get_priv_flags(src_cid);
		}

		if (vmci_deny_interaction(src_priv_flags, dst_priv_flags)) {
			result = VMCI_ERROR_NO_ACCESS;
			goto out;
		}
	}

	if (handle.context == VMCI_HOST_CONTEXT_ID) {
		result = vmci_dbell_host_context_notify(src_cid, handle);
	} else {
		spin_lock(&dst_context->lock);

		if (!vmci_handle_arr_has_entry(dst_context->doorbell_array,
					       handle)) {
			result = VMCI_ERROR_NOT_FOUND;
		} else {
			if (!vmci_handle_arr_has_entry(
					dst_context->pending_doorbell_array,
					handle)) {
				result = vmci_handle_arr_append_entry(
					&dst_context->pending_doorbell_array,
					handle);
				if (result == VMCI_SUCCESS) {
					ctx_signal_notify(dst_context);
					wake_up(&dst_context->host_context.wait_queue);
				}
			} else {
				result = VMCI_SUCCESS;
			}
		}
		spin_unlock(&dst_context->lock);
	}

 out:
	vmci_ctx_put(dst_context);

	return result;
}