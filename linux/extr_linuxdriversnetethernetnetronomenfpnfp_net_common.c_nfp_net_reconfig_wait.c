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
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  nfp_net_reconfig_check_done (struct nfp_net*,int) ; 
 int nn_readl (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int time_is_before_eq_jiffies (unsigned long) ; 

__attribute__((used)) static int nfp_net_reconfig_wait(struct nfp_net *nn, unsigned long deadline)
{
	bool timed_out = false;

	/* Poll update field, waiting for NFP to ack the config */
	while (!nfp_net_reconfig_check_done(nn, timed_out)) {
		msleep(1);
		timed_out = time_is_before_eq_jiffies(deadline);
	}

	if (nn_readl(nn, NFP_NET_CFG_UPDATE) & NFP_NET_CFG_UPDATE_ERR)
		return -EIO;

	return timed_out ? -EIO : 0;
}