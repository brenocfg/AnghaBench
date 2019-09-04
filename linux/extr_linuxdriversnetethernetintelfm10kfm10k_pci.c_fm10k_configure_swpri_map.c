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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
struct fm10k_intfc {int /*<<< orphan*/  flags; struct fm10k_hw hw; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_FLAG_SWPRI_CONFIG ; 
 int /*<<< orphan*/  FM10K_SWPRI_MAP (int) ; 
 int FM10K_SWPRI_MAX ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_mac_pf ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_get_prio_tc_map (struct net_device*,int) ; 

__attribute__((used)) static void fm10k_configure_swpri_map(struct fm10k_intfc *interface)
{
	struct net_device *netdev = interface->netdev;
	struct fm10k_hw *hw = &interface->hw;
	int i;

	/* clear flag indicating update is needed */
	clear_bit(FM10K_FLAG_SWPRI_CONFIG, interface->flags);

	/* these registers are only available on the PF */
	if (hw->mac.type != fm10k_mac_pf)
		return;

	/* configure SWPRI to PC map */
	for (i = 0; i < FM10K_SWPRI_MAX; i++)
		fm10k_write_reg(hw, FM10K_SWPRI_MAP(i),
				netdev_get_prio_tc_map(netdev, i));
}