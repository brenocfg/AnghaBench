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

/* Variables and functions */
 int /*<<< orphan*/  atomic_notifier_chain_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic_notifier_list ; 
 int /*<<< orphan*/  xen_panic_block ; 

int xen_panic_handler_init(void)
{
	atomic_notifier_chain_register(&panic_notifier_list, &xen_panic_block);
	return 0;
}