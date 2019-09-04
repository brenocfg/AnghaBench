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
struct timer_list {int dummy; } ;
struct nfp_net {int reconfig_timer_active; int /*<<< orphan*/  reconfig_lock; scalar_t__ reconfig_posted; scalar_t__ reconfig_sync_present; } ;

/* Variables and functions */
 struct nfp_net* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_reconfig_check_done (struct nfp_net*,int) ; 
 int /*<<< orphan*/  nfp_net_reconfig_start_async (struct nfp_net*,int /*<<< orphan*/ ) ; 
 struct nfp_net* nn ; 
 int /*<<< orphan*/  reconfig_timer ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_net_reconfig_timer(struct timer_list *t)
{
	struct nfp_net *nn = from_timer(nn, t, reconfig_timer);

	spin_lock_bh(&nn->reconfig_lock);

	nn->reconfig_timer_active = false;

	/* If sync caller is present it will take over from us */
	if (nn->reconfig_sync_present)
		goto done;

	/* Read reconfig status and report errors */
	nfp_net_reconfig_check_done(nn, true);

	if (nn->reconfig_posted)
		nfp_net_reconfig_start_async(nn, 0);
done:
	spin_unlock_bh(&nn->reconfig_lock);
}