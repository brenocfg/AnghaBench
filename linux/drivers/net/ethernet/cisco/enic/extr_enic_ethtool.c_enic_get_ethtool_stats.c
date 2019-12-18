#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct vnic_stats {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct enic {int /*<<< orphan*/  gen_stats; } ;
struct TYPE_6__ {size_t index; } ;
struct TYPE_5__ {size_t index; } ;
struct TYPE_4__ {size_t index; } ;

/* Variables and functions */
 int ENOMEM ; 
 int enic_dev_stats_dump (struct enic*,struct vnic_stats**) ; 
 TYPE_3__* enic_gen_stats ; 
 unsigned int enic_n_gen_stats ; 
 unsigned int enic_n_rx_stats ; 
 unsigned int enic_n_tx_stats ; 
 TYPE_2__* enic_rx_stats ; 
 TYPE_1__* enic_tx_stats ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void enic_get_ethtool_stats(struct net_device *netdev,
	struct ethtool_stats *stats, u64 *data)
{
	struct enic *enic = netdev_priv(netdev);
	struct vnic_stats *vstats;
	unsigned int i;
	int err;

	err = enic_dev_stats_dump(enic, &vstats);
	/* return only when pci_zalloc_consistent fails in vnic_dev_stats_dump
	 * For other failures, like devcmd failure, we return previously
	 * recorded stats.
	 */
	if (err == -ENOMEM)
		return;

	for (i = 0; i < enic_n_tx_stats; i++)
		*(data++) = ((u64 *)&vstats->tx)[enic_tx_stats[i].index];
	for (i = 0; i < enic_n_rx_stats; i++)
		*(data++) = ((u64 *)&vstats->rx)[enic_rx_stats[i].index];
	for (i = 0; i < enic_n_gen_stats; i++)
		*(data++) = ((u64 *)&enic->gen_stats)[enic_gen_stats[i].index];
}