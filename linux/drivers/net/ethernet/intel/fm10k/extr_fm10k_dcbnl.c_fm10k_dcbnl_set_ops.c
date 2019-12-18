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
struct net_device {int /*<<< orphan*/ * dcbnl_ops; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_dcbnl_ops ; 
 scalar_t__ fm10k_mac_pf ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

void fm10k_dcbnl_set_ops(struct net_device *dev)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	struct fm10k_hw *hw = &interface->hw;

	if (hw->mac.type == fm10k_mac_pf)
		dev->dcbnl_ops = &fm10k_dcbnl_ops;
}