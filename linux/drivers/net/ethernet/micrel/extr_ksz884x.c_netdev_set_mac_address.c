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
typedef  int /*<<< orphan*/  uint ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ksz_hw {int mac_override; int /*<<< orphan*/  override_addr; } ;
struct TYPE_2__ {scalar_t__ first_port; } ;
struct dev_priv {TYPE_1__ port; struct dev_info* adapter; } ;
struct dev_info {struct ksz_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  hw_add_addr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_block_intr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_del_addr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_restore_intr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_set_addr (struct ksz_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netdev_set_mac_address(struct net_device *dev, void *addr)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct sockaddr *mac = addr;
	uint interrupt;

	if (priv->port.first_port > 0)
		hw_del_addr(hw, dev->dev_addr);
	else {
		hw->mac_override = 1;
		memcpy(hw->override_addr, mac->sa_data, ETH_ALEN);
	}

	memcpy(dev->dev_addr, mac->sa_data, ETH_ALEN);

	interrupt = hw_block_intr(hw);

	if (priv->port.first_port > 0)
		hw_add_addr(hw, dev->dev_addr);
	else
		hw_set_addr(hw);
	hw_restore_intr(hw, interrupt);

	return 0;
}