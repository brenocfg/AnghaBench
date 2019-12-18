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
typedef  scalar_t__ u16 ;
struct e1000_mac_info {int serdes_has_link; scalar_t__ type; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_PCS_LSTAT ; 
 int E1000_PCS_LSTS_DUPLEX_FULL ; 
 int E1000_PCS_LSTS_LINK_OK ; 
 int E1000_PCS_LSTS_SPEED_100 ; 
 int E1000_PCS_LSTS_SPEED_1000 ; 
 int E1000_PCS_LSTS_SYNK_OK ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_2P5_SKU ; 
 int E1000_STATUS_2P5_SKU_OVER ; 
 scalar_t__ FULL_DUPLEX ; 
 scalar_t__ HALF_DUPLEX ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_2500 ; 
 scalar_t__ e1000_i354 ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 igb_get_pcs_speed_and_duplex_82575(struct e1000_hw *hw, u16 *speed,
						u16 *duplex)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 pcs, status;

	/* Set up defaults for the return values of this function */
	mac->serdes_has_link = false;
	*speed = 0;
	*duplex = 0;

	/* Read the PCS Status register for link state. For non-copper mode,
	 * the status register is not accurate. The PCS status register is
	 * used instead.
	 */
	pcs = rd32(E1000_PCS_LSTAT);

	/* The link up bit determines when link is up on autoneg. The sync ok
	 * gets set once both sides sync up and agree upon link. Stable link
	 * can be determined by checking for both link up and link sync ok
	 */
	if ((pcs & E1000_PCS_LSTS_LINK_OK) && (pcs & E1000_PCS_LSTS_SYNK_OK)) {
		mac->serdes_has_link = true;

		/* Detect and store PCS speed */
		if (pcs & E1000_PCS_LSTS_SPEED_1000)
			*speed = SPEED_1000;
		else if (pcs & E1000_PCS_LSTS_SPEED_100)
			*speed = SPEED_100;
		else
			*speed = SPEED_10;

		/* Detect and store PCS duplex */
		if (pcs & E1000_PCS_LSTS_DUPLEX_FULL)
			*duplex = FULL_DUPLEX;
		else
			*duplex = HALF_DUPLEX;

	/* Check if it is an I354 2.5Gb backplane connection. */
		if (mac->type == e1000_i354) {
			status = rd32(E1000_STATUS);
			if ((status & E1000_STATUS_2P5_SKU) &&
			    !(status & E1000_STATUS_2P5_SKU_OVER)) {
				*speed = SPEED_2500;
				*duplex = FULL_DUPLEX;
				hw_dbg("2500 Mbs, ");
				hw_dbg("Full Duplex\n");
			}
		}

	}

	return 0;
}