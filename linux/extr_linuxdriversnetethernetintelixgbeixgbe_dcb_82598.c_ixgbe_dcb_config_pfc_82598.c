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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int* low_water; int* high_water; int pause_time; } ;
struct ixgbe_hw {TYPE_1__ fc; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IXGBE_FCRTH (int) ; 
 int IXGBE_FCRTH_FCEN ; 
 int /*<<< orphan*/  IXGBE_FCRTL (int) ; 
 int IXGBE_FCRTL_XONE ; 
 int /*<<< orphan*/  IXGBE_FCRTV ; 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 int IXGBE_FCTRL_RFCE ; 
 int IXGBE_FCTRL_RPFCE ; 
 int /*<<< orphan*/  IXGBE_FCTTV (int) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RMCS ; 
 int IXGBE_RMCS_TFCE_802_3X ; 
 int IXGBE_RMCS_TFCE_PRIORITY ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int MAX_TRAFFIC_CLASS ; 

s32 ixgbe_dcb_config_pfc_82598(struct ixgbe_hw *hw, u8 pfc_en)
{
	u32 fcrtl, reg;
	u8  i;

	/* Enable Transmit Priority Flow Control */
	reg = IXGBE_READ_REG(hw, IXGBE_RMCS);
	reg &= ~IXGBE_RMCS_TFCE_802_3X;
	reg |= IXGBE_RMCS_TFCE_PRIORITY;
	IXGBE_WRITE_REG(hw, IXGBE_RMCS, reg);

	/* Enable Receive Priority Flow Control */
	reg = IXGBE_READ_REG(hw, IXGBE_FCTRL);
	reg &= ~(IXGBE_FCTRL_RPFCE | IXGBE_FCTRL_RFCE);

	if (pfc_en)
		reg |= IXGBE_FCTRL_RPFCE;

	IXGBE_WRITE_REG(hw, IXGBE_FCTRL, reg);

	/* Configure PFC Tx thresholds per TC */
	for (i = 0; i < MAX_TRAFFIC_CLASS; i++) {
		if (!(pfc_en & BIT(i))) {
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL(i), 0);
			IXGBE_WRITE_REG(hw, IXGBE_FCRTH(i), 0);
			continue;
		}

		fcrtl = (hw->fc.low_water[i] << 10) | IXGBE_FCRTL_XONE;
		reg = (hw->fc.high_water[i] << 10) | IXGBE_FCRTH_FCEN;
		IXGBE_WRITE_REG(hw, IXGBE_FCRTL(i), fcrtl);
		IXGBE_WRITE_REG(hw, IXGBE_FCRTH(i), reg);
	}

	/* Configure pause time */
	reg = hw->fc.pause_time * 0x00010001;
	for (i = 0; i < (MAX_TRAFFIC_CLASS / 2); i++)
		IXGBE_WRITE_REG(hw, IXGBE_FCTTV(i), reg);

	/* Configure flow control refresh threshold value */
	IXGBE_WRITE_REG(hw, IXGBE_FCRTV, hw->fc.pause_time / 2);


	return 0;
}