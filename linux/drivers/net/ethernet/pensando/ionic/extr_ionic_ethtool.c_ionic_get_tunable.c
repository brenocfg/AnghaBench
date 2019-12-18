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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ionic_lif {int /*<<< orphan*/  rx_copybreak; } ;
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_RX_COPYBREAK 128 
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ionic_get_tunable(struct net_device *netdev,
			     const struct ethtool_tunable *tuna, void *data)
{
	struct ionic_lif *lif = netdev_priv(netdev);

	switch (tuna->id) {
	case ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = lif->rx_copybreak;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}