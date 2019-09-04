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
struct nicvf {int /*<<< orphan*/  cq_coalesce_usecs; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 struct nicvf* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nicvf_get_coalesce(struct net_device *netdev,
			      struct ethtool_coalesce *cmd)
{
	struct nicvf *nic = netdev_priv(netdev);

	cmd->rx_coalesce_usecs = nic->cq_coalesce_usecs;
	return 0;
}