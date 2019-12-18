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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct ntb_netdev {int /*<<< orphan*/  qp; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ntb_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  ntb_transport_link_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_transport_link_up (int /*<<< orphan*/ ) ; 
 int ntb_transport_max_size (int /*<<< orphan*/ ) ; 
 int ntb_transport_rx_enqueue (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* ntb_transport_rx_remove (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ntb_netdev_change_mtu(struct net_device *ndev, int new_mtu)
{
	struct ntb_netdev *dev = netdev_priv(ndev);
	struct sk_buff *skb;
	int len, rc;

	if (new_mtu > ntb_transport_max_size(dev->qp) - ETH_HLEN)
		return -EINVAL;

	if (!netif_running(ndev)) {
		ndev->mtu = new_mtu;
		return 0;
	}

	/* Bring down the link and dispose of posted rx entries */
	ntb_transport_link_down(dev->qp);

	if (ndev->mtu < new_mtu) {
		int i;

		for (i = 0; (skb = ntb_transport_rx_remove(dev->qp, &len)); i++)
			dev_kfree_skb(skb);

		for (; i; i--) {
			skb = netdev_alloc_skb(ndev, new_mtu + ETH_HLEN);
			if (!skb) {
				rc = -ENOMEM;
				goto err;
			}

			rc = ntb_transport_rx_enqueue(dev->qp, skb, skb->data,
						      new_mtu + ETH_HLEN);
			if (rc) {
				dev_kfree_skb(skb);
				goto err;
			}
		}
	}

	ndev->mtu = new_mtu;

	ntb_transport_link_up(dev->qp);

	return 0;

err:
	ntb_transport_link_down(dev->qp);

	while ((skb = ntb_transport_rx_remove(dev->qp, &len)))
		dev_kfree_skb(skb);

	netdev_err(ndev, "Error changing MTU, device inoperable\n");
	return rc;
}