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
struct sky2_port {int dummy; } ;
struct sky2_hw {int ports; int flags; int /*<<< orphan*/  napi; struct net_device** dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  B0_Y2_SP_LISR ; 
 int SKY2_HW_IRQ_SETUP ; 
 int /*<<< orphan*/  Y2_IS_BASE ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/ * portirq_msk ; 
 int /*<<< orphan*/  sky2_hw_up (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_set_multicast (struct net_device*) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_all_up(struct sky2_hw *hw)
{
	u32 imask = Y2_IS_BASE;
	int i;

	for (i = 0; i < hw->ports; i++) {
		struct net_device *dev = hw->dev[i];
		struct sky2_port *sky2 = netdev_priv(dev);

		if (!netif_running(dev))
			continue;

		sky2_hw_up(sky2);
		sky2_set_multicast(dev);
		imask |= portirq_msk[i];
		netif_wake_queue(dev);
	}

	if (hw->flags & SKY2_HW_IRQ_SETUP) {
		sky2_write32(hw, B0_IMSK, imask);
		sky2_read32(hw, B0_IMSK);
		sky2_read32(hw, B0_Y2_SP_LISR);
		napi_enable(&hw->napi);
	}
}