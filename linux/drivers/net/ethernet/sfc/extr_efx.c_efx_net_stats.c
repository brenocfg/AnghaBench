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
struct rtnl_link_stats64 {int dummy; } ;
struct net_device {int dummy; } ;
struct efx_nic {int /*<<< orphan*/  stats_lock; TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_stats ) (struct efx_nic*,int /*<<< orphan*/ *,struct rtnl_link_stats64*) ;} ;

/* Variables and functions */
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*,int /*<<< orphan*/ *,struct rtnl_link_stats64*) ; 

__attribute__((used)) static void efx_net_stats(struct net_device *net_dev,
			  struct rtnl_link_stats64 *stats)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	spin_lock_bh(&efx->stats_lock);
	efx->type->update_stats(efx, NULL, stats);
	spin_unlock_bh(&efx->stats_lock);
}