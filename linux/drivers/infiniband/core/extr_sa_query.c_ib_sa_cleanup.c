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
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_nl_timed_work ; 
 int /*<<< orphan*/  ib_nl_wq ; 
 int /*<<< orphan*/  ib_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcast_cleanup () ; 
 int /*<<< orphan*/  queries ; 
 int /*<<< orphan*/  sa_client ; 
 int /*<<< orphan*/  xa_empty (int /*<<< orphan*/ *) ; 

void ib_sa_cleanup(void)
{
	cancel_delayed_work(&ib_nl_timed_work);
	flush_workqueue(ib_nl_wq);
	destroy_workqueue(ib_nl_wq);
	mcast_cleanup();
	ib_unregister_client(&sa_client);
	WARN_ON(!xa_empty(&queries));
}