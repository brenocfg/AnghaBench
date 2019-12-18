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
struct vmci_host_dev {scalar_t__ ct_type; int /*<<< orphan*/ * context; } ;
struct inode {int dummy; } ;
struct file {struct vmci_host_dev* private_data; } ;

/* Variables and functions */
 scalar_t__ VMCIOBJ_CONTEXT ; 
 scalar_t__ VMCIOBJ_NOT_SET ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmci_host_dev*) ; 
 int /*<<< orphan*/  vmci_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_host_active_users ; 

__attribute__((used)) static int vmci_host_close(struct inode *inode, struct file *filp)
{
	struct vmci_host_dev *vmci_host_dev = filp->private_data;

	if (vmci_host_dev->ct_type == VMCIOBJ_CONTEXT) {
		vmci_ctx_destroy(vmci_host_dev->context);
		vmci_host_dev->context = NULL;

		/*
		 * The number of active contexts is used to track whether any
		 * VMX'en are using the host personality. It is incremented when
		 * a context is created through the IOCTL_VMCI_INIT_CONTEXT
		 * ioctl.
		 */
		atomic_dec(&vmci_host_active_users);
	}
	vmci_host_dev->ct_type = VMCIOBJ_NOT_SET;

	kfree(vmci_host_dev);
	filp->private_data = NULL;
	return 0;
}