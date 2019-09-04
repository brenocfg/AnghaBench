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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  addr_wq ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nb ; 
 int /*<<< orphan*/  req_list ; 
 int /*<<< orphan*/  unregister_netevent_notifier (int /*<<< orphan*/ *) ; 

void addr_cleanup(void)
{
	unregister_netevent_notifier(&nb);
	destroy_workqueue(addr_wq);
	WARN_ON(!list_empty(&req_list));
}