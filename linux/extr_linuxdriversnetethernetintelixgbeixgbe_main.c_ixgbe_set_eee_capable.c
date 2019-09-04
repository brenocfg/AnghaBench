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
struct TYPE_2__ {int /*<<< orphan*/  eee_speeds_advertised; int /*<<< orphan*/  eee_speeds_supported; } ;
struct ixgbe_hw {int device_id; TYPE_1__ phy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  flags2; struct ixgbe_hw hw; } ;

/* Variables and functions */
#define  IXGBE_DEV_ID_X550EM_A_1G_T 129 
#define  IXGBE_DEV_ID_X550EM_A_1G_T_L 128 
 int /*<<< orphan*/  IXGBE_FLAG2_EEE_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_FLAG2_EEE_ENABLED ; 

__attribute__((used)) static void ixgbe_set_eee_capable(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;

	switch (hw->device_id) {
	case IXGBE_DEV_ID_X550EM_A_1G_T:
	case IXGBE_DEV_ID_X550EM_A_1G_T_L:
		if (!hw->phy.eee_speeds_supported)
			break;
		adapter->flags2 |= IXGBE_FLAG2_EEE_CAPABLE;
		if (!hw->phy.eee_speeds_advertised)
			break;
		adapter->flags2 |= IXGBE_FLAG2_EEE_ENABLED;
		break;
	default:
		adapter->flags2 &= ~IXGBE_FLAG2_EEE_CAPABLE;
		adapter->flags2 &= ~IXGBE_FLAG2_EEE_ENABLED;
		break;
	}
}