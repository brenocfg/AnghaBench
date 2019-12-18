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
struct virtnet_info {int max_queue_pairs; TYPE_2__* sq; } ;
struct net_device {int flags; } ;
struct ethtool_coalesce {int rx_max_coalesced_frames; int tx_max_coalesced_frames; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  ec_default ;
struct TYPE_3__ {int weight; } ;
struct TYPE_4__ {TYPE_1__ napi; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETHTOOL_SCOALESCE ; 
 int IFF_UP ; 
 int NAPI_POLL_WEIGHT ; 
 scalar_t__ memcmp (struct ethtool_coalesce*,struct ethtool_coalesce*,int) ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int virtnet_set_coalesce(struct net_device *dev,
				struct ethtool_coalesce *ec)
{
	struct ethtool_coalesce ec_default = {
		.cmd = ETHTOOL_SCOALESCE,
		.rx_max_coalesced_frames = 1,
	};
	struct virtnet_info *vi = netdev_priv(dev);
	int i, napi_weight;

	if (ec->tx_max_coalesced_frames > 1)
		return -EINVAL;

	ec_default.tx_max_coalesced_frames = ec->tx_max_coalesced_frames;
	napi_weight = ec->tx_max_coalesced_frames ? NAPI_POLL_WEIGHT : 0;

	/* disallow changes to fields not explicitly tested above */
	if (memcmp(ec, &ec_default, sizeof(ec_default)))
		return -EINVAL;

	if (napi_weight ^ vi->sq[0].napi.weight) {
		if (dev->flags & IFF_UP)
			return -EBUSY;
		for (i = 0; i < vi->max_queue_pairs; i++)
			vi->sq[i].napi.weight = napi_weight;
	}

	return 0;
}