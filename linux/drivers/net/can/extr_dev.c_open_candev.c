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
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ bitrate; } ;
struct TYPE_3__ {scalar_t__ bitrate; } ;
struct can_priv {int ctrlmode; TYPE_2__ bittiming; TYPE_1__ data_bittiming; } ;

/* Variables and functions */
 int CAN_CTRLMODE_FD ; 
 int EINVAL ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

int open_candev(struct net_device *dev)
{
	struct can_priv *priv = netdev_priv(dev);

	if (!priv->bittiming.bitrate) {
		netdev_err(dev, "bit-timing not yet defined\n");
		return -EINVAL;
	}

	/* For CAN FD the data bitrate has to be >= the arbitration bitrate */
	if ((priv->ctrlmode & CAN_CTRLMODE_FD) &&
	    (!priv->data_bittiming.bitrate ||
	     priv->data_bittiming.bitrate < priv->bittiming.bitrate)) {
		netdev_err(dev, "incorrect/missing data bit-timing\n");
		return -EINVAL;
	}

	/* Switch carrier on if device was stopped while in bus-off state */
	if (!netif_carrier_ok(dev))
		netif_carrier_on(dev);

	return 0;
}