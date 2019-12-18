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
struct TYPE_2__ {scalar_t__ netdev; } ;
struct nfp_net {TYPE_1__ dp; scalar_t__ reconfig_posted; int /*<<< orphan*/  reconfig_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  free_netdev (scalar_t__) ; 
 int /*<<< orphan*/  nfp_ccm_mbox_free (struct nfp_net*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (struct nfp_net*) ; 

void nfp_net_free(struct nfp_net *nn)
{
	WARN_ON(timer_pending(&nn->reconfig_timer) || nn->reconfig_posted);
	nfp_ccm_mbox_free(nn);

	if (nn->dp.netdev)
		free_netdev(nn->dp.netdev);
	else
		vfree(nn);
}