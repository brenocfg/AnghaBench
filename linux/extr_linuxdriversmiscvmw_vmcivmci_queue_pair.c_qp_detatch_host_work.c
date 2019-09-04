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
struct vmci_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_HOST_CONTEXT_ID ; 
 struct vmci_ctx* vmci_ctx_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_ctx_put (struct vmci_ctx*) ; 
 int vmci_qp_broker_detach (struct vmci_handle,struct vmci_ctx*) ; 

__attribute__((used)) static int qp_detatch_host_work(struct vmci_handle handle)
{
	int result;
	struct vmci_ctx *context;

	context = vmci_ctx_get(VMCI_HOST_CONTEXT_ID);

	result = vmci_qp_broker_detach(handle, context);

	vmci_ctx_put(context);
	return result;
}