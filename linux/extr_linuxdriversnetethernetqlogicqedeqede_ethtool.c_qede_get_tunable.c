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
struct qede_dev {int /*<<< orphan*/  rx_copybreak; } ;
struct net_device {int dummy; } ;
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_RX_COPYBREAK 128 
 struct qede_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int qede_get_tunable(struct net_device *dev,
			    const struct ethtool_tunable *tuna, void *data)
{
	struct qede_dev *edev = netdev_priv(dev);

	switch (tuna->id) {
	case ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = edev->rx_copybreak;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}