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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ice_q_stats {int dummy; } ;
struct ice_netdev_priv {TYPE_1__* vsi; } ;
struct TYPE_2__ {int alloc_txq; int alloc_rxq; } ;

/* Variables and functions */
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ice_q_stats_len(struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);

	return ((np->vsi->alloc_txq + np->vsi->alloc_rxq) *
		(sizeof(struct ice_q_stats) / sizeof(u64)));
}