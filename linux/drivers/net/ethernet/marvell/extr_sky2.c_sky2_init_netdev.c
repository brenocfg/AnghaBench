#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  syncp; } ;
struct TYPE_5__ {int /*<<< orphan*/  syncp; } ;
struct sky2_port {int flags; int duplex; int speed; int wol; unsigned int port; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  advertising; int /*<<< orphan*/  flow_mode; TYPE_2__ rx_stats; TYPE_1__ tx_stats; int /*<<< orphan*/  msg_enable; struct sky2_hw* hw; struct net_device* netdev; } ;
struct sky2_hw {scalar_t__ chip_id; int flags; scalar_t__ regs; TYPE_3__* pdev; struct net_device** dev; } ;
struct net_device {int hw_features; int features; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  vlan_features; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  irq; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {TYPE_4__ dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 scalar_t__ B2_MAC_1 ; 
 scalar_t__ CHIP_ID_YUKON_FE ; 
 scalar_t__ CHIP_ID_YUKON_FE_P ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_DATA_LEN ; 
 int /*<<< orphan*/  ETH_JUMBO_MTU ; 
 int /*<<< orphan*/  ETH_ZLEN ; 
 int /*<<< orphan*/  FC_BOTH ; 
 int /*<<< orphan*/  IS_ERR (void const*) ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  RX_DEF_PENDING ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_4__*) ; 
 int SKY2_FLAG_AUTO_PAUSE ; 
 int SKY2_FLAG_AUTO_SPEED ; 
 int SKY2_HW_RSS_BROKEN ; 
 int SKY2_HW_VLAN_BROKEN ; 
 int /*<<< orphan*/  SKY2_VLAN_OFFLOADS ; 
 int /*<<< orphan*/  TX_DEF_PENDING ; 
 int /*<<< orphan*/  TX_WATCHDOG ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  default_msg ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* of_get_mac_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup_ring_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_ethtool_ops ; 
 int /*<<< orphan*/ * sky2_netdev_ops ; 
 scalar_t__ sky2_set_mac_address (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  sky2_supported_modes (struct sky2_hw*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device *sky2_init_netdev(struct sky2_hw *hw, unsigned port,
					   int highmem, int wol)
{
	struct sky2_port *sky2;
	struct net_device *dev = alloc_etherdev(sizeof(*sky2));
	const void *iap;

	if (!dev)
		return NULL;

	SET_NETDEV_DEV(dev, &hw->pdev->dev);
	dev->irq = hw->pdev->irq;
	dev->ethtool_ops = &sky2_ethtool_ops;
	dev->watchdog_timeo = TX_WATCHDOG;
	dev->netdev_ops = &sky2_netdev_ops[port];

	sky2 = netdev_priv(dev);
	sky2->netdev = dev;
	sky2->hw = hw;
	sky2->msg_enable = netif_msg_init(debug, default_msg);

	u64_stats_init(&sky2->tx_stats.syncp);
	u64_stats_init(&sky2->rx_stats.syncp);

	/* Auto speed and flow control */
	sky2->flags = SKY2_FLAG_AUTO_SPEED | SKY2_FLAG_AUTO_PAUSE;
	if (hw->chip_id != CHIP_ID_YUKON_XL)
		dev->hw_features |= NETIF_F_RXCSUM;

	sky2->flow_mode = FC_BOTH;

	sky2->duplex = -1;
	sky2->speed = -1;
	sky2->advertising = sky2_supported_modes(hw);
	sky2->wol = wol;

	spin_lock_init(&sky2->phy_lock);

	sky2->tx_pending = TX_DEF_PENDING;
	sky2->tx_ring_size = roundup_ring_size(TX_DEF_PENDING);
	sky2->rx_pending = RX_DEF_PENDING;

	hw->dev[port] = dev;

	sky2->port = port;

	dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_SG | NETIF_F_TSO;

	if (highmem)
		dev->features |= NETIF_F_HIGHDMA;

	/* Enable receive hashing unless hardware is known broken */
	if (!(hw->flags & SKY2_HW_RSS_BROKEN))
		dev->hw_features |= NETIF_F_RXHASH;

	if (!(hw->flags & SKY2_HW_VLAN_BROKEN)) {
		dev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_HW_VLAN_CTAG_RX;
		dev->vlan_features |= SKY2_VLAN_OFFLOADS;
	}

	dev->features |= dev->hw_features;

	/* MTU range: 60 - 1500 or 9000 */
	dev->min_mtu = ETH_ZLEN;
	if (hw->chip_id == CHIP_ID_YUKON_FE ||
	    hw->chip_id == CHIP_ID_YUKON_FE_P)
		dev->max_mtu = ETH_DATA_LEN;
	else
		dev->max_mtu = ETH_JUMBO_MTU;

	/* try to get mac address in the following order:
	 * 1) from device tree data
	 * 2) from internal registers set by bootloader
	 */
	iap = of_get_mac_address(hw->pdev->dev.of_node);
	if (!IS_ERR(iap))
		ether_addr_copy(dev->dev_addr, iap);
	else
		memcpy_fromio(dev->dev_addr, hw->regs + B2_MAC_1 + port * 8,
			      ETH_ALEN);

	/* if the address is invalid, use a random value */
	if (!is_valid_ether_addr(dev->dev_addr)) {
		struct sockaddr sa = { AF_UNSPEC };

		netdev_warn(dev,
			    "Invalid MAC address, defaulting to random\n");
		eth_hw_addr_random(dev);
		memcpy(sa.sa_data, dev->dev_addr, ETH_ALEN);
		if (sky2_set_mac_address(dev, &sa))
			netdev_warn(dev, "Failed to set MAC address.\n");
	}

	return dev;
}