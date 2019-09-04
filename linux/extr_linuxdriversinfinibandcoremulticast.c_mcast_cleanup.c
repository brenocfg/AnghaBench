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
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_sa_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcast_client ; 
 int /*<<< orphan*/  mcast_wq ; 
 int /*<<< orphan*/  sa_client ; 

void mcast_cleanup(void)
{
	ib_unregister_client(&mcast_client);
	ib_sa_unregister_client(&sa_client);
	destroy_workqueue(mcast_wq);
}