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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_RTTPCS ; 
 size_t IXGBE_RTTPCS_ARBDIS ; 
 size_t IXGBE_RTTPCS_ARBD_DCB ; 
 size_t IXGBE_RTTPCS_ARBD_SHIFT ; 
 size_t IXGBE_RTTPCS_TPPAC ; 
 size_t IXGBE_RTTPCS_TPRM ; 
 int /*<<< orphan*/  IXGBE_RTTPT2C (size_t) ; 
 size_t IXGBE_RTTPT2C_BWG_SHIFT ; 
 size_t IXGBE_RTTPT2C_GSP ; 
 size_t IXGBE_RTTPT2C_LSP ; 
 size_t IXGBE_RTTPT2C_MCL_SHIFT ; 
 int /*<<< orphan*/  IXGBE_RTTUP2TC ; 
 size_t IXGBE_RTTUP2TC_UP_SHIFT ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,size_t) ; 
 size_t MAX_TRAFFIC_CLASS ; 
 size_t MAX_USER_PRIORITY ; 
 size_t prio_group ; 
 size_t prio_link ; 

s32 ixgbe_dcb_config_tx_data_arbiter_82599(struct ixgbe_hw *hw,
					   u16 *refill,
					   u16 *max,
					   u8 *bwg_id,
					   u8 *prio_type,
					   u8 *prio_tc)
{
	u32 reg;
	u8 i;

	/*
	 * Disable the arbiter before changing parameters
	 * (always enable recycle mode; SP; arb delay)
	 */
	reg = IXGBE_RTTPCS_TPPAC | IXGBE_RTTPCS_TPRM |
	      (IXGBE_RTTPCS_ARBD_DCB << IXGBE_RTTPCS_ARBD_SHIFT) |
	      IXGBE_RTTPCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTTPCS, reg);

	/* Map all traffic classes to their UP */
	reg = 0;
	for (i = 0; i < MAX_USER_PRIORITY; i++)
		reg |= (prio_tc[i] << (i * IXGBE_RTTUP2TC_UP_SHIFT));
	IXGBE_WRITE_REG(hw, IXGBE_RTTUP2TC, reg);

	/* Configure traffic class credits and priority */
	for (i = 0; i < MAX_TRAFFIC_CLASS; i++) {
		reg = refill[i];
		reg |= (u32)(max[i]) << IXGBE_RTTPT2C_MCL_SHIFT;
		reg |= (u32)(bwg_id[i]) << IXGBE_RTTPT2C_BWG_SHIFT;

		if (prio_type[i] == prio_group)
			reg |= IXGBE_RTTPT2C_GSP;

		if (prio_type[i] == prio_link)
			reg |= IXGBE_RTTPT2C_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_RTTPT2C(i), reg);
	}

	/*
	 * Configure Tx packet plane (recycle mode; SP; arb delay) and
	 * enable arbiter
	 */
	reg = IXGBE_RTTPCS_TPPAC | IXGBE_RTTPCS_TPRM |
	      (IXGBE_RTTPCS_ARBD_DCB << IXGBE_RTTPCS_ARBD_SHIFT);
	IXGBE_WRITE_REG(hw, IXGBE_RTTPCS, reg);

	return 0;
}