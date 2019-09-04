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
typedef  int u8 ;
struct sky2_port {int dummy; } ;
struct sky2_hw {struct net_device** dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  rx_fifo_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_IRQ_SRC ; 
 int /*<<< orphan*/  GMF_CLI_RX_FO ; 
 int /*<<< orphan*/  GMF_CLI_TX_FU ; 
 int GM_IS_RX_CO_OV ; 
 int GM_IS_RX_FF_OR ; 
 int GM_IS_TX_CO_OV ; 
 int GM_IS_TX_FF_UR ; 
 int /*<<< orphan*/  GM_RX_IRQ_SRC ; 
 int /*<<< orphan*/  GM_TX_IRQ_SRC ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int /*<<< orphan*/  gma_read16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct sky2_port*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int sky2_read8 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_mac_intr(struct sky2_hw *hw, unsigned port)
{
	struct net_device *dev = hw->dev[port];
	struct sky2_port *sky2 = netdev_priv(dev);
	u8 status = sky2_read8(hw, SK_REG(port, GMAC_IRQ_SRC));

	netif_info(sky2, intr, dev, "mac interrupt status 0x%x\n", status);

	if (status & GM_IS_RX_CO_OV)
		gma_read16(hw, port, GM_RX_IRQ_SRC);

	if (status & GM_IS_TX_CO_OV)
		gma_read16(hw, port, GM_TX_IRQ_SRC);

	if (status & GM_IS_RX_FF_OR) {
		++dev->stats.rx_fifo_errors;
		sky2_write8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_CLI_RX_FO);
	}

	if (status & GM_IS_TX_FF_UR) {
		++dev->stats.tx_fifo_errors;
		sky2_write8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_CLI_TX_FU);
	}
}