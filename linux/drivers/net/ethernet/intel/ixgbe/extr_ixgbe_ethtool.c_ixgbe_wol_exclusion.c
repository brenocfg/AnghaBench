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
struct ixgbe_hw {int /*<<< orphan*/  subsystem_device_id; int /*<<< orphan*/  device_id; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;
struct ethtool_wolinfo {scalar_t__ supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_wol_supported (struct ixgbe_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_wol_exclusion(struct ixgbe_adapter *adapter,
			       struct ethtool_wolinfo *wol)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int retval = 0;

	/* WOL not supported for all devices */
	if (!ixgbe_wol_supported(adapter, hw->device_id,
				 hw->subsystem_device_id)) {
		retval = 1;
		wol->supported = 0;
	}

	return retval;
}