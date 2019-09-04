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
struct netdev_notifier_changeupper_info {int /*<<< orphan*/  upper_dev; } ;

/* Variables and functions */
 unsigned long NETDEV_CHANGEUPPER ; 
 unsigned long NETDEV_PRECHANGEUPPER ; 
 int netif_is_l3_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mlxsw_sp_is_vrf_event(unsigned long event, void *ptr)
{
	struct netdev_notifier_changeupper_info *info = ptr;

	if (event != NETDEV_PRECHANGEUPPER && event != NETDEV_CHANGEUPPER)
		return false;
	return netif_is_l3_master(info->upper_dev);
}