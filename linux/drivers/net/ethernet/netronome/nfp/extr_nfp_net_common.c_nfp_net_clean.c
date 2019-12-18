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
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;
struct nfp_net {TYPE_1__ dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_ccm_mbox_clean (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_reconfig_wait_posted (struct nfp_net*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

void nfp_net_clean(struct nfp_net *nn)
{
	if (!nn->dp.netdev)
		return;

	unregister_netdev(nn->dp.netdev);
	nfp_ccm_mbox_clean(nn);
	nfp_net_reconfig_wait_posted(nn);
}