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
typedef  int /*<<< orphan*/  vstats ;
struct rtnl_link_stats64 {int dummy; } ;
struct opa_vnic_stats {int /*<<< orphan*/  netstats; } ;
struct opa_vnic_adapter {int /*<<< orphan*/  stats_lock; TYPE_1__* rn_ops; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_get_stats64 ) (struct net_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct rtnl_link_stats64*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct opa_vnic_stats*,int /*<<< orphan*/ ,int) ; 
 struct opa_vnic_adapter* opa_vnic_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void opa_vnic_get_stats64(struct net_device *netdev,
				 struct rtnl_link_stats64 *stats)
{
	struct opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	struct opa_vnic_stats vstats;

	memset(&vstats, 0, sizeof(vstats));
	spin_lock(&adapter->stats_lock);
	adapter->rn_ops->ndo_get_stats64(netdev, &vstats.netstats);
	spin_unlock(&adapter->stats_lock);
	memcpy(stats, &vstats.netstats, sizeof(*stats));
}