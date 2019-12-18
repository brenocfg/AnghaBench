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
struct nfp_net_dp {int mtu; } ;
struct nfp_net {int /*<<< orphan*/  app; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int nfp_app_check_mtu (int /*<<< orphan*/ ,struct net_device*,int) ; 
 struct nfp_net_dp* nfp_net_clone_dp (struct nfp_net*) ; 
 int nfp_net_ring_reconfig (struct nfp_net*,struct nfp_net_dp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfp_net_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct nfp_net *nn = netdev_priv(netdev);
	struct nfp_net_dp *dp;
	int err;

	err = nfp_app_check_mtu(nn->app, netdev, new_mtu);
	if (err)
		return err;

	dp = nfp_net_clone_dp(nn);
	if (!dp)
		return -ENOMEM;

	dp->mtu = new_mtu;

	return nfp_net_ring_reconfig(nn, dp, NULL);
}