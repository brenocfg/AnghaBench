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
 int /*<<< orphan*/  i40iw_inetaddr6_notifier ; 
 int /*<<< orphan*/  i40iw_inetaddr_notifier ; 
 int /*<<< orphan*/  i40iw_net_notifier ; 
 int /*<<< orphan*/  i40iw_netdevice_notifier ; 
 int /*<<< orphan*/  register_inet6addr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_inetaddr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_netevent_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40iw_register_notifiers(void)
{
	register_inetaddr_notifier(&i40iw_inetaddr_notifier);
	register_inet6addr_notifier(&i40iw_inetaddr6_notifier);
	register_netevent_notifier(&i40iw_net_notifier);
	register_netdevice_notifier(&i40iw_netdevice_notifier);
}