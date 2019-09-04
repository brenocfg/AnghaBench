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
struct net_device {int dummy; } ;
struct fs_enet_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPM_CR_RESTART_TX ; 
 struct fs_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  scc_cr_cmd (struct fs_enet_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_restart(struct net_device *dev)
{
	struct fs_enet_private *fep = netdev_priv(dev);

	scc_cr_cmd(fep, CPM_CR_RESTART_TX);
}