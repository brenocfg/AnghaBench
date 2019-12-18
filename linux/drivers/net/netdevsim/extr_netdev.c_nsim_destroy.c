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
struct netdevsim {struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  nsim_bpf_uninit (struct netdevsim*) ; 
 int /*<<< orphan*/  nsim_ipsec_teardown (struct netdevsim*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

void nsim_destroy(struct netdevsim *ns)
{
	struct net_device *dev = ns->netdev;

	rtnl_lock();
	unregister_netdevice(dev);
	nsim_ipsec_teardown(ns);
	nsim_bpf_uninit(ns);
	rtnl_unlock();
	free_netdev(dev);
}