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
struct skge_port {int /*<<< orphan*/  netdev; } ;
struct skge_hw {struct net_device** dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  rx_fifo_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_IRQ_SRC ; 
 int /*<<< orphan*/  GMF_CLI_RX_FO ; 
 int /*<<< orphan*/  GMF_CLI_TX_FU ; 
 int GM_IS_RX_FF_OR ; 
 int GM_IS_TX_FF_UR ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  SK_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int /*<<< orphan*/  intr ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_printk (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int skge_read8 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yukon_mac_intr(struct skge_hw *hw, int port)
{
	struct net_device *dev = hw->dev[port];
	struct skge_port *skge = netdev_priv(dev);
	u8 status = skge_read8(hw, SK_REG(port, GMAC_IRQ_SRC));

	netif_printk(skge, intr, KERN_DEBUG, skge->netdev,
		     "mac interrupt status 0x%x\n", status);

	if (status & GM_IS_RX_FF_OR) {
		++dev->stats.rx_fifo_errors;
		skge_write8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_CLI_RX_FO);
	}

	if (status & GM_IS_TX_FF_UR) {
		++dev->stats.tx_fifo_errors;
		skge_write8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_CLI_TX_FU);
	}

}