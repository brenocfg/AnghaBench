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
struct nfp_net {int /*<<< orphan*/  reconfig_lock; int /*<<< orphan*/  reconfig_posted; int /*<<< orphan*/  reconfig_timer_active; scalar_t__ reconfig_sync_present; } ;

/* Variables and functions */
 scalar_t__ nfp_net_reconfig_check_done (struct nfp_net*,int) ; 
 int /*<<< orphan*/  nfp_net_reconfig_start_async (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_net_reconfig_post(struct nfp_net *nn, u32 update)
{
	spin_lock_bh(&nn->reconfig_lock);

	/* Sync caller will kick off async reconf when it's done, just post */
	if (nn->reconfig_sync_present) {
		nn->reconfig_posted |= update;
		goto done;
	}

	/* Opportunistically check if the previous command is done */
	if (!nn->reconfig_timer_active ||
	    nfp_net_reconfig_check_done(nn, false))
		nfp_net_reconfig_start_async(nn, update);
	else
		nn->reconfig_posted |= update;
done:
	spin_unlock_bh(&nn->reconfig_lock);
}