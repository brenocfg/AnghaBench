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
struct netfront_info {int /*<<< orphan*/  tx_stats; int /*<<< orphan*/  rx_stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct netfront_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xennet_free_netdev(struct net_device *netdev)
{
	struct netfront_info *np = netdev_priv(netdev);

	free_percpu(np->rx_stats);
	free_percpu(np->tx_stats);
	free_netdev(netdev);
}