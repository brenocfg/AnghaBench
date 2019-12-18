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
struct net {int dummy; } ;
struct ipvlan_netns {int /*<<< orphan*/  ipvl_nf_hook_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  ipvlan_netid ; 
 int /*<<< orphan*/  ipvlan_register_nf_hook (struct net*) ; 
 int /*<<< orphan*/  ipvlan_unregister_nf_hook (struct net*) ; 
 struct ipvlan_netns* net_generic (struct net*,int /*<<< orphan*/ ) ; 

void ipvlan_migrate_l3s_hook(struct net *oldnet, struct net *newnet)
{
	struct ipvlan_netns *old_vnet;

	ASSERT_RTNL();

	old_vnet = net_generic(oldnet, ipvlan_netid);
	if (!old_vnet->ipvl_nf_hook_refcnt)
		return;

	ipvlan_register_nf_hook(newnet);
	ipvlan_unregister_nf_hook(oldnet);
}