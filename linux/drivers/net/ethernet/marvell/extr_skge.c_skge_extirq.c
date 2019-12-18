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
struct skge_port {int dummy; } ;
struct skge_hw {int ports; scalar_t__ phy_type; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  intr_mask; int /*<<< orphan*/  phy_lock; struct net_device** dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  IS_EXT_REG ; 
 scalar_t__ SK_PHY_BCOM ; 
 int /*<<< orphan*/  bcom_phy_intr (struct skge_port*) ; 
 int /*<<< orphan*/  is_genesis (struct skge_hw*) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  skge_read32 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yukon_phy_intr (struct skge_port*) ; 

__attribute__((used)) static void skge_extirq(unsigned long arg)
{
	struct skge_hw *hw = (struct skge_hw *) arg;
	int port;

	for (port = 0; port < hw->ports; port++) {
		struct net_device *dev = hw->dev[port];

		if (netif_running(dev)) {
			struct skge_port *skge = netdev_priv(dev);

			spin_lock(&hw->phy_lock);
			if (!is_genesis(hw))
				yukon_phy_intr(skge);
			else if (hw->phy_type == SK_PHY_BCOM)
				bcom_phy_intr(skge);
			spin_unlock(&hw->phy_lock);
		}
	}

	spin_lock_irq(&hw->hw_lock);
	hw->intr_mask |= IS_EXT_REG;
	skge_write32(hw, B0_IMSK, hw->intr_mask);
	skge_read32(hw, B0_IMSK);
	spin_unlock_irq(&hw->hw_lock);
}