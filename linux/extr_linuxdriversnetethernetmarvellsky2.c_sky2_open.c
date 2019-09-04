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
typedef  int /*<<< orphan*/  u32 ;
struct sky2_port {unsigned int port; struct sky2_hw* hw; } ;
struct sky2_hw {int ports; scalar_t__ chip_id; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 scalar_t__ CHIP_ID_YUKON_OPT ; 
 scalar_t__ CHIP_ID_YUKON_OP_2 ; 
 scalar_t__ CHIP_ID_YUKON_PRM ; 
 int /*<<< orphan*/  Y2_IS_PHY_QLNK ; 
 int /*<<< orphan*/  ifup ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct sky2_port*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/ * portirq_msk ; 
 int sky2_alloc_buffers (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_free_buffers (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_hw_up (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int sky2_setup_irq (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_open(struct net_device *dev)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	u32 imask;
	int err;

	netif_carrier_off(dev);

	err = sky2_alloc_buffers(sky2);
	if (err)
		goto err_out;

	/* With single port, IRQ is setup when device is brought up */
	if (hw->ports == 1 && (err = sky2_setup_irq(hw, dev->name)))
		goto err_out;

	sky2_hw_up(sky2);

	/* Enable interrupts from phy/mac for port */
	imask = sky2_read32(hw, B0_IMSK);

	if (hw->chip_id == CHIP_ID_YUKON_OPT ||
	    hw->chip_id == CHIP_ID_YUKON_PRM ||
	    hw->chip_id == CHIP_ID_YUKON_OP_2)
		imask |= Y2_IS_PHY_QLNK;	/* enable PHY Quick Link */

	imask |= portirq_msk[port];
	sky2_write32(hw, B0_IMSK, imask);
	sky2_read32(hw, B0_IMSK);

	netif_info(sky2, ifup, dev, "enabling interface\n");

	return 0;

err_out:
	sky2_free_buffers(sky2);
	return err;
}