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
 int ENOMEM ; 
 int /*<<< orphan*/  addr_wq ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb ; 
 int /*<<< orphan*/  register_netevent_notifier (int /*<<< orphan*/ *) ; 

int addr_init(void)
{
	addr_wq = alloc_ordered_workqueue("ib_addr", 0);
	if (!addr_wq)
		return -ENOMEM;

	register_netevent_notifier(&nb);

	return 0;
}