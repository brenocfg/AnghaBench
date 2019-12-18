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
struct qcauart {int /*<<< orphan*/  rx_skb; TYPE_2__* net_dev; int /*<<< orphan*/  tx_buffer; TYPE_1__* serdev; } ;
struct net_device {int /*<<< orphan*/  type; int /*<<< orphan*/  mtu; } ;
struct TYPE_4__ {scalar_t__ mtu; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t QCAFRM_FOOTER_LEN ; 
 size_t QCAFRM_HEADER_LEN ; 
 size_t QCAFRM_MAX_LEN ; 
 int /*<<< orphan*/  QCAFRM_MAX_MTU ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  devm_kmalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_alloc_skb_ip_align (TYPE_2__*,scalar_t__) ; 
 struct qcauart* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int qcauart_netdev_init(struct net_device *dev)
{
	struct qcauart *qca = netdev_priv(dev);
	size_t len;

	/* Finish setting up the device info. */
	dev->mtu = QCAFRM_MAX_MTU;
	dev->type = ARPHRD_ETHER;

	len = QCAFRM_HEADER_LEN + QCAFRM_MAX_LEN + QCAFRM_FOOTER_LEN;
	qca->tx_buffer = devm_kmalloc(&qca->serdev->dev, len, GFP_KERNEL);
	if (!qca->tx_buffer)
		return -ENOMEM;

	qca->rx_skb = netdev_alloc_skb_ip_align(qca->net_dev,
						qca->net_dev->mtu +
						VLAN_ETH_HLEN);
	if (!qca->rx_skb)
		return -ENOBUFS;

	return 0;
}