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
struct vmci_ctx {int /*<<< orphan*/  lock; int /*<<< orphan*/  pending_datagrams; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vmci_ctx* vmci_ctx_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_ctx_put (struct vmci_ctx*) ; 

int vmci_ctx_pending_datagrams(u32 cid, u32 *pending)
{
	struct vmci_ctx *context;

	context = vmci_ctx_get(cid);
	if (context == NULL)
		return VMCI_ERROR_INVALID_ARGS;

	spin_lock(&context->lock);
	if (pending)
		*pending = context->pending_datagrams;
	spin_unlock(&context->lock);
	vmci_ctx_put(context);

	return VMCI_SUCCESS;
}