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
struct wilc {int /*<<< orphan*/ * monitor_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (int /*<<< orphan*/ *) ; 

void wilc_wfi_deinit_mon_interface(struct wilc *wl, bool rtnl_locked)
{
	if (!wl->monitor_dev)
		return;

	if (rtnl_locked)
		unregister_netdevice(wl->monitor_dev);
	else
		unregister_netdev(wl->monitor_dev);
	wl->monitor_dev = NULL;
}