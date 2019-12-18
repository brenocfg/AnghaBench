#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct skge_port {int duplex; int speed; int wol; int port; int /*<<< orphan*/  link_timer; int /*<<< orphan*/  advertising; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  autoneg; TYPE_2__ rx_ring; TYPE_1__ tx_ring; int /*<<< orphan*/  msg_enable; struct skge_hw* hw; struct net_device* netdev; int /*<<< orphan*/  napi; } ;
struct skge_hw {scalar_t__ regs; struct net_device** dev; TYPE_3__* pdev; } ;
struct net_device {int features; int hw_features; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  irq; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 scalar_t__ B2_MAC_1 ; 
 int /*<<< orphan*/  DEFAULT_RX_RING_SIZE ; 
 int /*<<< orphan*/  DEFAULT_TX_RING_SIZE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_JUMBO_MTU ; 
 int /*<<< orphan*/  ETH_ZLEN ; 
 int /*<<< orphan*/  FLOW_MODE_SYM_OR_REM ; 
 int /*<<< orphan*/  NAPI_WEIGHT ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TX_WATCHDOG ; 
 int WAKE_MAGIC ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  default_msg ; 
 scalar_t__ device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_genesis (struct skge_hw*) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_ethtool_ops ; 
 int /*<<< orphan*/  skge_netdev_ops ; 
 int /*<<< orphan*/  skge_poll ; 
 int /*<<< orphan*/  skge_supported_modes (struct skge_hw*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wol_supported (struct skge_hw*) ; 
 int /*<<< orphan*/  xm_link_timer ; 

__attribute__((used)) static struct net_device *skge_devinit(struct skge_hw *hw, int port,
				       int highmem)
{
	struct skge_port *skge;
	struct net_device *dev = alloc_etherdev(sizeof(*skge));

	if (!dev)
		return NULL;

	SET_NETDEV_DEV(dev, &hw->pdev->dev);
	dev->netdev_ops = &skge_netdev_ops;
	dev->ethtool_ops = &skge_ethtool_ops;
	dev->watchdog_timeo = TX_WATCHDOG;
	dev->irq = hw->pdev->irq;

	/* MTU range: 60 - 9000 */
	dev->min_mtu = ETH_ZLEN;
	dev->max_mtu = ETH_JUMBO_MTU;

	if (highmem)
		dev->features |= NETIF_F_HIGHDMA;

	skge = netdev_priv(dev);
	netif_napi_add(dev, &skge->napi, skge_poll, NAPI_WEIGHT);
	skge->netdev = dev;
	skge->hw = hw;
	skge->msg_enable = netif_msg_init(debug, default_msg);

	skge->tx_ring.count = DEFAULT_TX_RING_SIZE;
	skge->rx_ring.count = DEFAULT_RX_RING_SIZE;

	/* Auto speed and flow control */
	skge->autoneg = AUTONEG_ENABLE;
	skge->flow_control = FLOW_MODE_SYM_OR_REM;
	skge->duplex = -1;
	skge->speed = -1;
	skge->advertising = skge_supported_modes(hw);

	if (device_can_wakeup(&hw->pdev->dev)) {
		skge->wol = wol_supported(hw) & WAKE_MAGIC;
		device_set_wakeup_enable(&hw->pdev->dev, skge->wol);
	}

	hw->dev[port] = dev;

	skge->port = port;

	/* Only used for Genesis XMAC */
	if (is_genesis(hw))
	    timer_setup(&skge->link_timer, xm_link_timer, 0);
	else {
		dev->hw_features = NETIF_F_IP_CSUM | NETIF_F_SG |
		                   NETIF_F_RXCSUM;
		dev->features |= dev->hw_features;
	}

	/* read the mac address */
	memcpy_fromio(dev->dev_addr, hw->regs + B2_MAC_1 + port*8, ETH_ALEN);

	return dev;
}