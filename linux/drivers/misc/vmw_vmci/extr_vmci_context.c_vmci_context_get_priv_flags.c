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
struct vmci_ctx {int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_LEAST_PRIVILEGE_FLAGS ; 
 int /*<<< orphan*/  VMCI_NO_PRIVILEGE_FLAGS ; 
 struct vmci_ctx* vmci_ctx_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_ctx_put (struct vmci_ctx*) ; 
 scalar_t__ vmci_host_code_active () ; 

u32 vmci_context_get_priv_flags(u32 context_id)
{
	if (vmci_host_code_active()) {
		u32 flags;
		struct vmci_ctx *context;

		context = vmci_ctx_get(context_id);
		if (!context)
			return VMCI_LEAST_PRIVILEGE_FLAGS;

		flags = context->priv_flags;
		vmci_ctx_put(context);
		return flags;
	}
	return VMCI_NO_PRIVILEGE_FLAGS;
}