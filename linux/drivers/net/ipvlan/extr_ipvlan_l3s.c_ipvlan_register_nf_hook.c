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
struct ipvlan_netns {int ipvl_nf_hook_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipvl_nfops ; 
 int /*<<< orphan*/  ipvlan_netid ; 
 struct ipvlan_netns* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int nf_register_net_hooks (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipvlan_register_nf_hook(struct net *net)
{
	struct ipvlan_netns *vnet = net_generic(net, ipvlan_netid);
	int err = 0;

	if (!vnet->ipvl_nf_hook_refcnt) {
		err = nf_register_net_hooks(net, ipvl_nfops,
					    ARRAY_SIZE(ipvl_nfops));
		if (!err)
			vnet->ipvl_nf_hook_refcnt = 1;
	} else {
		vnet->ipvl_nf_hook_refcnt++;
	}

	return err;
}