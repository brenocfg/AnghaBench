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
struct ethtool_tunable {int id; } ;
struct enic {int /*<<< orphan*/  rx_copybreak; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_RX_COPYBREAK 128 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enic_set_tunable(struct net_device *dev,
			    const struct ethtool_tunable *tuna,
			    const void *data)
{
	struct enic *enic = netdev_priv(dev);
	int ret = 0;

	switch (tuna->id) {
	case ETHTOOL_RX_COPYBREAK:
		enic->rx_copybreak = *(u32 *)data;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}