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
struct vmballoon {int /*<<< orphan*/  vmci_doorbell; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  VMCI_INVALID_ID ; 
 int /*<<< orphan*/  VMW_BALLOON_CMD_VMCI_DOORBELL_SET ; 
 int /*<<< orphan*/  vmballoon_cmd (struct vmballoon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_doorbell_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_handle_is_invalid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmballoon_vmci_cleanup(struct vmballoon *b)
{
	vmballoon_cmd(b, VMW_BALLOON_CMD_VMCI_DOORBELL_SET,
		      VMCI_INVALID_ID, VMCI_INVALID_ID);

	if (!vmci_handle_is_invalid(b->vmci_doorbell)) {
		vmci_doorbell_destroy(b->vmci_doorbell);
		b->vmci_doorbell = VMCI_INVALID_HANDLE;
	}
}