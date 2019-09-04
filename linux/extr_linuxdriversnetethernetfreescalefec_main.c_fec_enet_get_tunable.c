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
struct fec_enet_private {int /*<<< orphan*/  rx_copybreak; } ;
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_RX_COPYBREAK 128 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fec_enet_get_tunable(struct net_device *netdev,
				const struct ethtool_tunable *tuna,
				void *data)
{
	struct fec_enet_private *fep = netdev_priv(netdev);
	int ret = 0;

	switch (tuna->id) {
	case ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = fep->rx_copybreak;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}