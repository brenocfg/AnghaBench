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
struct nfp_net {int reconfig_sync_present; int /*<<< orphan*/  reconfig_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_net_reconfig_sync_enter (struct nfp_net*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_net_reconfig_wait_posted(struct nfp_net *nn)
{
	nfp_net_reconfig_sync_enter(nn);

	spin_lock_bh(&nn->reconfig_lock);
	nn->reconfig_sync_present = false;
	spin_unlock_bh(&nn->reconfig_lock);
}