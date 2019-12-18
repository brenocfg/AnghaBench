#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int type; } ;
struct ixgbe_hw {TYPE_2__ phy; int /*<<< orphan*/  device_id; TYPE_1__ mac; } ;
struct ixgbe_adapter {int flags; int flags2; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SFP ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SFP_N ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_X_SFP ; 
 int IXGBE_EICR_GPI_SDP0_X540 ; 
 int /*<<< orphan*/  IXGBE_EIMS ; 
 int IXGBE_EIMS_ECC ; 
 int IXGBE_EIMS_ENABLE_MASK ; 
 int IXGBE_EIMS_FLOW_DIR ; 
 int IXGBE_EIMS_GPI_SDP0 (struct ixgbe_hw*) ; 
 int IXGBE_EIMS_GPI_SDP1 (struct ixgbe_hw*) ; 
 int IXGBE_EIMS_GPI_SDP2 (struct ixgbe_hw*) ; 
 int IXGBE_EIMS_LSC ; 
 int IXGBE_EIMS_MAILBOX ; 
 int IXGBE_EIMS_RTX_QUEUE ; 
 int IXGBE_EIMS_TS ; 
 int IXGBE_FLAG2_FDIR_REQUIRES_REINIT ; 
 int IXGBE_FLAG2_TEMP_SENSOR_CAPABLE ; 
 int IXGBE_FLAG_FAN_FAIL_CAPABLE ; 
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 int IXGBE_FLAG_NEED_LINK_UPDATE ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_irq_enable_queues (struct ixgbe_adapter*,int /*<<< orphan*/ ) ; 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 int /*<<< orphan*/  ixgbe_phy_x550em_ext_t ; 

__attribute__((used)) static inline void ixgbe_irq_enable(struct ixgbe_adapter *adapter, bool queues,
				    bool flush)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 mask = (IXGBE_EIMS_ENABLE_MASK & ~IXGBE_EIMS_RTX_QUEUE);

	/* don't reenable LSC while waiting for link */
	if (adapter->flags & IXGBE_FLAG_NEED_LINK_UPDATE)
		mask &= ~IXGBE_EIMS_LSC;

	if (adapter->flags2 & IXGBE_FLAG2_TEMP_SENSOR_CAPABLE)
		switch (adapter->hw.mac.type) {
		case ixgbe_mac_82599EB:
			mask |= IXGBE_EIMS_GPI_SDP0(hw);
			break;
		case ixgbe_mac_X540:
		case ixgbe_mac_X550:
		case ixgbe_mac_X550EM_x:
		case ixgbe_mac_x550em_a:
			mask |= IXGBE_EIMS_TS;
			break;
		default:
			break;
		}
	if (adapter->flags & IXGBE_FLAG_FAN_FAIL_CAPABLE)
		mask |= IXGBE_EIMS_GPI_SDP1(hw);
	switch (adapter->hw.mac.type) {
	case ixgbe_mac_82599EB:
		mask |= IXGBE_EIMS_GPI_SDP1(hw);
		mask |= IXGBE_EIMS_GPI_SDP2(hw);
		/* fall through */
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		if (adapter->hw.device_id == IXGBE_DEV_ID_X550EM_X_SFP ||
		    adapter->hw.device_id == IXGBE_DEV_ID_X550EM_A_SFP ||
		    adapter->hw.device_id == IXGBE_DEV_ID_X550EM_A_SFP_N)
			mask |= IXGBE_EIMS_GPI_SDP0(&adapter->hw);
		if (adapter->hw.phy.type == ixgbe_phy_x550em_ext_t)
			mask |= IXGBE_EICR_GPI_SDP0_X540;
		mask |= IXGBE_EIMS_ECC;
		mask |= IXGBE_EIMS_MAILBOX;
		break;
	default:
		break;
	}

	if ((adapter->flags & IXGBE_FLAG_FDIR_HASH_CAPABLE) &&
	    !(adapter->flags2 & IXGBE_FLAG2_FDIR_REQUIRES_REINIT))
		mask |= IXGBE_EIMS_FLOW_DIR;

	IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMS, mask);
	if (queues)
		ixgbe_irq_enable_queues(adapter, ~0);
	if (flush)
		IXGBE_WRITE_FLUSH(&adapter->hw);
}