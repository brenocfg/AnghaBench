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
typedef  void* u32 ;
struct nfp_net_dp {void* txd_cnt; void* rxd_cnt; } ;
struct nfp_net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct nfp_net_dp* nfp_net_clone_dp (struct nfp_net*) ; 
 int nfp_net_ring_reconfig (struct nfp_net*,struct nfp_net_dp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfp_net_set_ring_size(struct nfp_net *nn, u32 rxd_cnt, u32 txd_cnt)
{
	struct nfp_net_dp *dp;

	dp = nfp_net_clone_dp(nn);
	if (!dp)
		return -ENOMEM;

	dp->rxd_cnt = rxd_cnt;
	dp->txd_cnt = txd_cnt;

	return nfp_net_ring_reconfig(nn, dp, NULL);
}