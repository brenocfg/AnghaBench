#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ibmveth_adapter {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  IBMVETH_GET_STAT (struct ibmveth_adapter*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ibmveth_stats ; 
 struct ibmveth_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ibmveth_get_ethtool_stats(struct net_device *dev,
				      struct ethtool_stats *stats, u64 *data)
{
	int i;
	struct ibmveth_adapter *adapter = netdev_priv(dev);

	for (i = 0; i < ARRAY_SIZE(ibmveth_stats); i++)
		data[i] = IBMVETH_GET_STAT(adapter, ibmveth_stats[i].offset);
}