#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfp_net_dp {TYPE_1__* netdev; int /*<<< orphan*/  mtu; } ;
struct nfp_net {struct nfp_net_dp dp; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_is_rxfh_configured (TYPE_1__*) ; 
 int /*<<< orphan*/  nfp_net_rss_init_itbl (struct nfp_net*) ; 

__attribute__((used)) static void nfp_net_dp_swap(struct nfp_net *nn, struct nfp_net_dp *dp)
{
	struct nfp_net_dp new_dp = *dp;

	*dp = nn->dp;
	nn->dp = new_dp;

	nn->dp.netdev->mtu = new_dp.mtu;

	if (!netif_is_rxfh_configured(nn->dp.netdev))
		nfp_net_rss_init_itbl(nn);
}