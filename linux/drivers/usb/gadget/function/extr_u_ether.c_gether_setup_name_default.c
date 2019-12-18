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
struct net_device {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; } ;
struct eth_dev {int /*<<< orphan*/  host_mac; int /*<<< orphan*/  dev_mac; int /*<<< orphan*/  qmult; struct net_device* net; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_reqs; int /*<<< orphan*/  tx_reqs; int /*<<< orphan*/  work; int /*<<< orphan*/  req_lock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  GETHER_MAX_ETH_FRAME_LEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QMULT_DEFAULT ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  eth_netdev_ops ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_work ; 
 int /*<<< orphan*/  gadget_type ; 
 struct eth_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct net_device *gether_setup_name_default(const char *netname)
{
	struct net_device	*net;
	struct eth_dev		*dev;

	net = alloc_etherdev(sizeof(*dev));
	if (!net)
		return ERR_PTR(-ENOMEM);

	dev = netdev_priv(net);
	spin_lock_init(&dev->lock);
	spin_lock_init(&dev->req_lock);
	INIT_WORK(&dev->work, eth_work);
	INIT_LIST_HEAD(&dev->tx_reqs);
	INIT_LIST_HEAD(&dev->rx_reqs);

	skb_queue_head_init(&dev->rx_frames);

	/* network device setup */
	dev->net = net;
	dev->qmult = QMULT_DEFAULT;
	snprintf(net->name, sizeof(net->name), "%s%%d", netname);

	eth_random_addr(dev->dev_mac);
	pr_warn("using random %s ethernet address\n", "self");
	eth_random_addr(dev->host_mac);
	pr_warn("using random %s ethernet address\n", "host");

	net->netdev_ops = &eth_netdev_ops;

	net->ethtool_ops = &ops;
	SET_NETDEV_DEVTYPE(net, &gadget_type);

	/* MTU range: 14 - 15412 */
	net->min_mtu = ETH_HLEN;
	net->max_mtu = GETHER_MAX_ETH_FRAME_LEN;

	return net;
}