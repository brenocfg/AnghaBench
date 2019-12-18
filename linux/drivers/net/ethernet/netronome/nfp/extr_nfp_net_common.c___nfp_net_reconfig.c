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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_net {int reconfig_sync_present; int /*<<< orphan*/  reconfig_lock; scalar_t__ reconfig_posted; } ;

/* Variables and functions */
 int HZ ; 
 int NFP_NET_POLL_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  nfp_net_reconfig_start (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_reconfig_start_async (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_reconfig_sync_enter (struct nfp_net*) ; 
 int nfp_net_reconfig_wait (struct nfp_net*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int __nfp_net_reconfig(struct nfp_net *nn, u32 update)
{
	int ret;

	nfp_net_reconfig_sync_enter(nn);

	nfp_net_reconfig_start(nn, update);
	ret = nfp_net_reconfig_wait(nn, jiffies + HZ * NFP_NET_POLL_TIMEOUT);

	spin_lock_bh(&nn->reconfig_lock);

	if (nn->reconfig_posted)
		nfp_net_reconfig_start_async(nn, 0);

	nn->reconfig_sync_present = false;

	spin_unlock_bh(&nn->reconfig_lock);

	return ret;
}