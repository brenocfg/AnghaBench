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
struct TYPE_2__ {int /*<<< orphan*/  resource; int /*<<< orphan*/  context; } ;
struct vmballoon {int capabilities; TYPE_1__ vmci_doorbell; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VMCI_FLAG_DELAYED_CB ; 
 int /*<<< orphan*/  VMCI_PRIVILEGE_FLAG_RESTRICTED ; 
 unsigned long VMCI_SUCCESS ; 
 int /*<<< orphan*/  VMW_BALLOON_CMD_VMCI_DOORBELL_SET ; 
 int VMW_BALLOON_SIGNALLED_WAKEUP_CMD ; 
 unsigned long VMW_BALLOON_SUCCESS ; 
 unsigned long __vmballoon_cmd (struct vmballoon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmballoon_doorbell ; 
 int /*<<< orphan*/  vmballoon_vmci_cleanup (struct vmballoon*) ; 
 unsigned long vmci_doorbell_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmballoon*) ; 

__attribute__((used)) static int vmballoon_vmci_init(struct vmballoon *b)
{
	unsigned long error;

	if ((b->capabilities & VMW_BALLOON_SIGNALLED_WAKEUP_CMD) == 0)
		return 0;

	error = vmci_doorbell_create(&b->vmci_doorbell, VMCI_FLAG_DELAYED_CB,
				     VMCI_PRIVILEGE_FLAG_RESTRICTED,
				     vmballoon_doorbell, b);

	if (error != VMCI_SUCCESS)
		goto fail;

	error =	__vmballoon_cmd(b, VMW_BALLOON_CMD_VMCI_DOORBELL_SET,
				b->vmci_doorbell.context,
				b->vmci_doorbell.resource, NULL);

	if (error != VMW_BALLOON_SUCCESS)
		goto fail;

	return 0;
fail:
	vmballoon_vmci_cleanup(b);
	return -EIO;
}