#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct spider_net_card {struct net_device* netdev; TYPE_1__* pdev; scalar_t__ ignore_rx_ramfull; scalar_t__ num_rx_ints; int /*<<< orphan*/  napi; int /*<<< orphan*/  aneg_timer; scalar_t__ aneg_count; int /*<<< orphan*/  tx_timer; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int hw_features; int features; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIDER_NET_MAX_MTU ; 
 int /*<<< orphan*/  SPIDER_NET_MIN_MTU ; 
 int /*<<< orphan*/  SPIDER_NET_NAPI_WEIGHT ; 
 scalar_t__ SPIDER_NET_RX_CSUM_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_probe (struct spider_net_card*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* pci_device_to_OF_node (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_set_drvdata (TYPE_1__*,struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spider_net_cleanup_tx_ring ; 
 int /*<<< orphan*/  spider_net_link_phy ; 
 int /*<<< orphan*/  spider_net_poll ; 
 int spider_net_set_mac (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  spider_net_setup_netdev_ops (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spider_net_setup_netdev(struct spider_net_card *card)
{
	int result;
	struct net_device *netdev = card->netdev;
	struct device_node *dn;
	struct sockaddr addr;
	const u8 *mac;

	SET_NETDEV_DEV(netdev, &card->pdev->dev);

	pci_set_drvdata(card->pdev, netdev);

	timer_setup(&card->tx_timer, spider_net_cleanup_tx_ring, 0);
	netdev->irq = card->pdev->irq;

	card->aneg_count = 0;
	timer_setup(&card->aneg_timer, spider_net_link_phy, 0);

	netif_napi_add(netdev, &card->napi,
		       spider_net_poll, SPIDER_NET_NAPI_WEIGHT);

	spider_net_setup_netdev_ops(netdev);

	netdev->hw_features = NETIF_F_RXCSUM | NETIF_F_IP_CSUM;
	if (SPIDER_NET_RX_CSUM_DEFAULT)
		netdev->features |= NETIF_F_RXCSUM;
	netdev->features |= NETIF_F_IP_CSUM | NETIF_F_LLTX;
	/* some time: NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
	 *		NETIF_F_HW_VLAN_CTAG_FILTER */

	/* MTU range: 64 - 2294 */
	netdev->min_mtu = SPIDER_NET_MIN_MTU;
	netdev->max_mtu = SPIDER_NET_MAX_MTU;

	netdev->irq = card->pdev->irq;
	card->num_rx_ints = 0;
	card->ignore_rx_ramfull = 0;

	dn = pci_device_to_OF_node(card->pdev);
	if (!dn)
		return -EIO;

	mac = of_get_property(dn, "local-mac-address", NULL);
	if (!mac)
		return -EIO;
	memcpy(addr.sa_data, mac, ETH_ALEN);

	result = spider_net_set_mac(netdev, &addr);
	if ((result) && (netif_msg_probe(card)))
		dev_err(&card->netdev->dev,
		        "Failed to set MAC address: %i\n", result);

	result = register_netdev(netdev);
	if (result) {
		if (netif_msg_probe(card))
			dev_err(&card->netdev->dev,
			        "Couldn't register net_device: %i\n", result);
		return result;
	}

	if (netif_msg_probe(card))
		pr_info("Initialized device %s.\n", netdev->name);

	return 0;
}