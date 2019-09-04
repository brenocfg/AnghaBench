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
struct vmci_ctx {int /*<<< orphan*/  list_item; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_1__ ctx_list ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  vmci_ctx_put (struct vmci_ctx*) ; 

void vmci_ctx_destroy(struct vmci_ctx *context)
{
	spin_lock(&ctx_list.lock);
	list_del_rcu(&context->list_item);
	spin_unlock(&ctx_list.lock);
	synchronize_rcu();

	vmci_ctx_put(context);
}