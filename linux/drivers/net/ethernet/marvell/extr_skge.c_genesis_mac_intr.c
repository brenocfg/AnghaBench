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
typedef  int u16 ;
struct skge_port {int /*<<< orphan*/  link_timer; int /*<<< orphan*/  netdev; } ;
struct skge_hw {scalar_t__ phy_type; struct net_device** dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_fifo_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ SK_PHY_XMAC ; 
 int /*<<< orphan*/  XM_ISRC ; 
 int XM_IS_INP_ASS ; 
 int XM_IS_TXF_UR ; 
 int /*<<< orphan*/  XM_MD_FTF ; 
 int /*<<< orphan*/  XM_MODE ; 
 int /*<<< orphan*/  intr ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_printk (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xm_link_down (struct skge_hw*,int) ; 
 int xm_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xm_write32 (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void genesis_mac_intr(struct skge_hw *hw, int port)
{
	struct net_device *dev = hw->dev[port];
	struct skge_port *skge = netdev_priv(dev);
	u16 status = xm_read16(hw, port, XM_ISRC);

	netif_printk(skge, intr, KERN_DEBUG, skge->netdev,
		     "mac interrupt status 0x%x\n", status);

	if (hw->phy_type == SK_PHY_XMAC && (status & XM_IS_INP_ASS)) {
		xm_link_down(hw, port);
		mod_timer(&skge->link_timer, jiffies + 1);
	}

	if (status & XM_IS_TXF_UR) {
		xm_write32(hw, port, XM_MODE, XM_MD_FTF);
		++dev->stats.tx_fifo_errors;
	}
}