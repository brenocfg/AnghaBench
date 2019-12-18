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
struct TYPE_3__ {int type; } ;
struct qeth_card {TYPE_2__* gdev; TYPE_1__ info; } ;
struct net_device {int min_mtu; int /*<<< orphan*/  features; int /*<<< orphan*/  vlan_features; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * ethtool_ops; scalar_t__ mtu; scalar_t__ max_mtu; int /*<<< orphan*/  watchdog_timeo; struct qeth_card* ml_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 scalar_t__ IS_OSN (struct qeth_card*) ; 
 int /*<<< orphan*/  NETIF_F_SG ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
#define  QETH_CARD_TYPE_IQD 130 
#define  QETH_CARD_TYPE_OSM 129 
#define  QETH_CARD_TYPE_OSN 128 
 int /*<<< orphan*/  QETH_IQD_MIN_TXQ ; 
 int /*<<< orphan*/  QETH_MAX_QUEUES ; 
 int /*<<< orphan*/  QETH_TX_TIMEOUT ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int /*<<< orphan*/ ) ; 
 struct net_device* alloc_etherdev_mqs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct net_device* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* alloc_netdev_mqs (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_ethtool_ops ; 
 int /*<<< orphan*/  qeth_osn_ethtool_ops ; 

__attribute__((used)) static struct net_device *qeth_alloc_netdev(struct qeth_card *card)
{
	struct net_device *dev;

	switch (card->info.type) {
	case QETH_CARD_TYPE_IQD:
		dev = alloc_netdev_mqs(0, "hsi%d", NET_NAME_UNKNOWN,
				       ether_setup, QETH_MAX_QUEUES, 1);
		break;
	case QETH_CARD_TYPE_OSM:
		dev = alloc_etherdev(0);
		break;
	case QETH_CARD_TYPE_OSN:
		dev = alloc_netdev(0, "osn%d", NET_NAME_UNKNOWN, ether_setup);
		break;
	default:
		dev = alloc_etherdev_mqs(0, QETH_MAX_QUEUES, 1);
	}

	if (!dev)
		return NULL;

	dev->ml_priv = card;
	dev->watchdog_timeo = QETH_TX_TIMEOUT;
	dev->min_mtu = IS_OSN(card) ? 64 : 576;
	 /* initialized when device first goes online: */
	dev->max_mtu = 0;
	dev->mtu = 0;
	SET_NETDEV_DEV(dev, &card->gdev->dev);
	netif_carrier_off(dev);

	if (IS_OSN(card)) {
		dev->ethtool_ops = &qeth_osn_ethtool_ops;
	} else {
		dev->ethtool_ops = &qeth_ethtool_ops;
		dev->priv_flags &= ~IFF_TX_SKB_SHARING;
		dev->hw_features |= NETIF_F_SG;
		dev->vlan_features |= NETIF_F_SG;
		if (IS_IQD(card)) {
			dev->features |= NETIF_F_SG;
			if (netif_set_real_num_tx_queues(dev,
							 QETH_IQD_MIN_TXQ)) {
				free_netdev(dev);
				return NULL;
			}
		}
	}

	return dev;
}