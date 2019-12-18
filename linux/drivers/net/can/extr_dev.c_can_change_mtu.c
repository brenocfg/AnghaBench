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
struct net_device {int flags; int mtu; } ;
struct can_priv {int ctrlmode_static; int ctrlmode; int ctrlmode_supported; } ;

/* Variables and functions */
#define  CANFD_MTU 129 
 int CAN_CTRLMODE_FD ; 
#define  CAN_MTU 128 
 int EBUSY ; 
 int EINVAL ; 
 int IFF_UP ; 
 struct can_priv* netdev_priv (struct net_device*) ; 

int can_change_mtu(struct net_device *dev, int new_mtu)
{
	struct can_priv *priv = netdev_priv(dev);

	/* Do not allow changing the MTU while running */
	if (dev->flags & IFF_UP)
		return -EBUSY;

	/* allow change of MTU according to the CANFD ability of the device */
	switch (new_mtu) {
	case CAN_MTU:
		/* 'CANFD-only' controllers can not switch to CAN_MTU */
		if (priv->ctrlmode_static & CAN_CTRLMODE_FD)
			return -EINVAL;

		priv->ctrlmode &= ~CAN_CTRLMODE_FD;
		break;

	case CANFD_MTU:
		/* check for potential CANFD ability */
		if (!(priv->ctrlmode_supported & CAN_CTRLMODE_FD) &&
		    !(priv->ctrlmode_static & CAN_CTRLMODE_FD))
			return -EINVAL;

		priv->ctrlmode |= CAN_CTRLMODE_FD;
		break;

	default:
		return -EINVAL;
	}

	dev->mtu = new_mtu;
	return 0;
}