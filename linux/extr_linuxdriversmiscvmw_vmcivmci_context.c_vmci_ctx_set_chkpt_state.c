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
typedef  int u32 ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_OBSOLETE ; 
 int VMCI_NOTIFICATION_CPT_STATE ; 
 int VMCI_SUCCESS ; 
 int VMCI_WELLKNOWN_CPT_STATE ; 
 int /*<<< orphan*/  pr_devel (char*,int,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int vmci_ctx_add_notification (int,int) ; 

int vmci_ctx_set_chkpt_state(u32 context_id,
			     u32 cpt_type,
			     u32 buf_size,
			     void *cpt_buf)
{
	u32 i;
	u32 current_id;
	int result = VMCI_SUCCESS;
	u32 num_ids = buf_size / sizeof(u32);

	if (cpt_type == VMCI_WELLKNOWN_CPT_STATE && num_ids > 0) {
		/*
		 * We would end up here if VMX with VM to VM communication
		 * attempts to restore a checkpoint with wellknown handles.
		 */
		pr_warn("Attempt to restore checkpoint with obsolete wellknown handles\n");
		return VMCI_ERROR_OBSOLETE;
	}

	if (cpt_type != VMCI_NOTIFICATION_CPT_STATE) {
		pr_devel("Invalid cpt state (type=%d)\n", cpt_type);
		return VMCI_ERROR_INVALID_ARGS;
	}

	for (i = 0; i < num_ids && result == VMCI_SUCCESS; i++) {
		current_id = ((u32 *)cpt_buf)[i];
		result = vmci_ctx_add_notification(context_id, current_id);
		if (result != VMCI_SUCCESS)
			break;
	}
	if (result != VMCI_SUCCESS)
		pr_devel("Failed to set cpt state (type=%d) (error=%d)\n",
			 cpt_type, result);

	return result;
}