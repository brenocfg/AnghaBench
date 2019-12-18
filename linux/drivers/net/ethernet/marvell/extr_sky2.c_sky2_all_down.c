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
struct sky2_port {int dummy; } ;
struct sky2_hw {int flags; int ports; struct net_device** dev; int /*<<< orphan*/  napi; TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 int SKY2_HW_IRQ_SETUP ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  sky2_hw_down (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_all_down(struct sky2_hw *hw)
{
	int i;

	if (hw->flags & SKY2_HW_IRQ_SETUP) {
		sky2_write32(hw, B0_IMSK, 0);
		sky2_read32(hw, B0_IMSK);

		synchronize_irq(hw->pdev->irq);
		napi_disable(&hw->napi);
	}

	for (i = 0; i < hw->ports; i++) {
		struct net_device *dev = hw->dev[i];
		struct sky2_port *sky2 = netdev_priv(dev);

		if (!netif_running(dev))
			continue;

		netif_carrier_off(dev);
		netif_tx_disable(dev);
		sky2_hw_down(sky2);
	}
}