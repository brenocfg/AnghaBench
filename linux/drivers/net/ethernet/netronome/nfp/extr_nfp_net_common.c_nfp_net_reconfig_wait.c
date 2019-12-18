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
struct nfp_net {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE ; 
 int NFP_NET_CFG_UPDATE_ERR ; 
 scalar_t__ __nfp_net_reconfig_wait (struct nfp_net*,unsigned long) ; 
 int nn_readl (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_net_reconfig_wait(struct nfp_net *nn, unsigned long deadline)
{
	if (__nfp_net_reconfig_wait(nn, deadline))
		return -EIO;

	if (nn_readl(nn, NFP_NET_CFG_UPDATE) & NFP_NET_CFG_UPDATE_ERR)
		return -EIO;

	return 0;
}