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
struct vmci_host_dev {scalar_t__ ct_type; struct vmci_ctx* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait_queue; } ;
struct vmci_ctx {scalar_t__ pending_datagrams; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending_doorbell_array; TYPE_1__ host_context; } ;
struct file {struct vmci_host_dev* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 scalar_t__ VMCIOBJ_CONTEXT ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vmci_handle_arr_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __poll_t vmci_host_poll(struct file *filp, poll_table *wait)
{
	struct vmci_host_dev *vmci_host_dev = filp->private_data;
	struct vmci_ctx *context = vmci_host_dev->context;
	__poll_t mask = 0;

	if (vmci_host_dev->ct_type == VMCIOBJ_CONTEXT) {
		/* Check for VMCI calls to this VM context. */
		if (wait)
			poll_wait(filp, &context->host_context.wait_queue,
				  wait);

		spin_lock(&context->lock);
		if (context->pending_datagrams > 0 ||
		    vmci_handle_arr_get_size(
				context->pending_doorbell_array) > 0) {
			mask = EPOLLIN;
		}
		spin_unlock(&context->lock);
	}
	return mask;
}