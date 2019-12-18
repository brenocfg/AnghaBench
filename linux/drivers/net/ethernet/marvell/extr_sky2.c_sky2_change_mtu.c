#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sky2_port {unsigned int port; scalar_t__ speed; struct sky2_hw* hw; } ;
struct sky2_hw {int flags; int /*<<< orphan*/  napi; TYPE_1__* pdev; } ;
struct net_device {int mtu; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  B0_Y2_SP_LISR ; 
 int /*<<< orphan*/  DATA_BLIND_DEF ; 
 int DATA_BLIND_VAL (int /*<<< orphan*/ ) ; 
 int ETH_DATA_LEN ; 
 int GM_GPCR_RX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  GM_SERIAL_MODE ; 
 int GM_SMOD_JUMBO_ENA ; 
 int GM_SMOD_VLAN_ENA ; 
 int /*<<< orphan*/  IPG_DATA_DEF_1000 ; 
 int /*<<< orphan*/  IPG_DATA_DEF_10_100 ; 
 int IPG_DATA_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 int /*<<< orphan*/  RB_ENA_OP_MD ; 
 int SKY2_HW_RAM_BUFFER ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int gma_read16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/ * rxqaddr ; 
 int sky2_alloc_rx_skbs (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_rx_clean (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_rx_start (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_rx_stop (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_set_tx_stfwd (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_change_mtu(struct net_device *dev, int new_mtu)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	int err;
	u16 ctl, mode;
	u32 imask;

	if (!netif_running(dev)) {
		dev->mtu = new_mtu;
		netdev_update_features(dev);
		return 0;
	}

	imask = sky2_read32(hw, B0_IMSK);
	sky2_write32(hw, B0_IMSK, 0);
	sky2_read32(hw, B0_IMSK);

	netif_trans_update(dev);	/* prevent tx timeout */
	napi_disable(&hw->napi);
	netif_tx_disable(dev);

	synchronize_irq(hw->pdev->irq);

	if (!(hw->flags & SKY2_HW_RAM_BUFFER))
		sky2_set_tx_stfwd(hw, port);

	ctl = gma_read16(hw, port, GM_GP_CTRL);
	gma_write16(hw, port, GM_GP_CTRL, ctl & ~GM_GPCR_RX_ENA);
	sky2_rx_stop(sky2);
	sky2_rx_clean(sky2);

	dev->mtu = new_mtu;
	netdev_update_features(dev);

	mode = DATA_BLIND_VAL(DATA_BLIND_DEF) |	GM_SMOD_VLAN_ENA;
	if (sky2->speed > SPEED_100)
		mode |= IPG_DATA_VAL(IPG_DATA_DEF_1000);
	else
		mode |= IPG_DATA_VAL(IPG_DATA_DEF_10_100);

	if (dev->mtu > ETH_DATA_LEN)
		mode |= GM_SMOD_JUMBO_ENA;

	gma_write16(hw, port, GM_SERIAL_MODE, mode);

	sky2_write8(hw, RB_ADDR(rxqaddr[port], RB_CTRL), RB_ENA_OP_MD);

	err = sky2_alloc_rx_skbs(sky2);
	if (!err)
		sky2_rx_start(sky2);
	else
		sky2_rx_clean(sky2);
	sky2_write32(hw, B0_IMSK, imask);

	sky2_read32(hw, B0_Y2_SP_LISR);
	napi_enable(&hw->napi);

	if (err)
		dev_close(dev);
	else {
		gma_write16(hw, port, GM_GP_CTRL, ctl);

		netif_wake_queue(dev);
	}

	return err;
}