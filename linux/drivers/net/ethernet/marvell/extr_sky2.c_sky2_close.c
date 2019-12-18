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
struct sky2_port {size_t port; int /*<<< orphan*/  tx_le; struct sky2_hw* hw; } ;
struct sky2_hw {int ports; int /*<<< orphan*/  napi; TYPE_1__* pdev; int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  SKY2_HW_IRQ_SETUP ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sky2_hw*) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct sky2_port*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/ * portirq_msk ; 
 int /*<<< orphan*/  sky2_free_buffers (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_hw_down (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_close(struct net_device *dev)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;

	/* Never really got started! */
	if (!sky2->tx_le)
		return 0;

	netif_info(sky2, ifdown, dev, "disabling interface\n");

	if (hw->ports == 1) {
		sky2_write32(hw, B0_IMSK, 0);
		sky2_read32(hw, B0_IMSK);

		napi_disable(&hw->napi);
		free_irq(hw->pdev->irq, hw);
		hw->flags &= ~SKY2_HW_IRQ_SETUP;
	} else {
		u32 imask;

		/* Disable port IRQ */
		imask  = sky2_read32(hw, B0_IMSK);
		imask &= ~portirq_msk[sky2->port];
		sky2_write32(hw, B0_IMSK, imask);
		sky2_read32(hw, B0_IMSK);

		synchronize_irq(hw->pdev->irq);
		napi_synchronize(&hw->napi);
	}

	sky2_hw_down(sky2);

	sky2_free_buffers(sky2);

	return 0;
}