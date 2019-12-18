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
 int /*<<< orphan*/  lio_vf_rep_netdev_notifier ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

void
lio_vf_rep_modexit(void)
{
	if (unregister_netdevice_notifier(&lio_vf_rep_netdev_notifier))
		pr_err("netdev notifier unregister failed\n");
}