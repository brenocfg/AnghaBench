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
typedef  int /*<<< orphan*/  u32 ;
struct vmci_ctx {TYPE_1__* cred; } ;
typedef  int /*<<< orphan*/  kuid_t ;
struct TYPE_2__ {int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmci_ctx* vmci_ctx_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_ctx_put (struct vmci_ctx*) ; 
 scalar_t__ vmci_host_code_active () ; 

bool vmci_is_context_owner(u32 context_id, kuid_t uid)
{
	bool is_owner = false;

	if (vmci_host_code_active()) {
		struct vmci_ctx *context = vmci_ctx_get(context_id);
		if (context) {
			if (context->cred)
				is_owner = uid_eq(context->cred->uid, uid);
			vmci_ctx_put(context);
		}
	}

	return is_owner;
}