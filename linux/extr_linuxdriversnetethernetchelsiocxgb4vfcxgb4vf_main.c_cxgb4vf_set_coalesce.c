#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct port_info {size_t first_qset; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct TYPE_4__ {TYPE_1__* ethrxq; } ;
struct adapter {TYPE_2__ sge; } ;
struct TYPE_3__ {int /*<<< orphan*/  rspq; } ;

/* Variables and functions */
 struct port_info* netdev_priv (struct net_device*) ; 
 int set_rxq_intr_params (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgb4vf_set_coalesce(struct net_device *dev,
				struct ethtool_coalesce *coalesce)
{
	const struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	return set_rxq_intr_params(adapter,
				   &adapter->sge.ethrxq[pi->first_qset].rspq,
				   coalesce->rx_coalesce_usecs,
				   coalesce->rx_max_coalesced_frames);
}