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
typedef  int u32 ;
struct atl1c_hw {int rfd_burst; int ctrl_flags; scalar_t__ nic_type; int device_id; } ;
struct atl1c_adapter {struct atl1c_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPM_THRUPUT_LIMIT ; 
 int /*<<< orphan*/  ASPM_THRUPUT_LIMIT_100M ; 
 int ATL1C_RX_IPV6_CHKSUM ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 
 int FIELD_SETX (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IPV6_CHKSUM_CTRL_EN ; 
 int /*<<< orphan*/  REG_RXQ_CTRL ; 
 int RXQ_RFD_BURST_NUM_MASK ; 
 int RXQ_RFD_BURST_NUM_SHIFT ; 
 scalar_t__ athr_l1d_2 ; 

__attribute__((used)) static void atl1c_configure_rx(struct atl1c_adapter *adapter)
{
	struct atl1c_hw *hw = &adapter->hw;
	u32 rxq_ctrl_data;

	rxq_ctrl_data = (hw->rfd_burst & RXQ_RFD_BURST_NUM_MASK) <<
			RXQ_RFD_BURST_NUM_SHIFT;

	if (hw->ctrl_flags & ATL1C_RX_IPV6_CHKSUM)
		rxq_ctrl_data |= IPV6_CHKSUM_CTRL_EN;

	/* aspm for gigabit */
	if (hw->nic_type != athr_l1d_2 && (hw->device_id & 1) != 0)
		rxq_ctrl_data = FIELD_SETX(rxq_ctrl_data, ASPM_THRUPUT_LIMIT,
			ASPM_THRUPUT_LIMIT_100M);

	AT_WRITE_REG(hw, REG_RXQ_CTRL, rxq_ctrl_data);
}