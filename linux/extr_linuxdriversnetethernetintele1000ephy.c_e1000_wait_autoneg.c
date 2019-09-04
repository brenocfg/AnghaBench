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
typedef  scalar_t__ u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ BMSR_ANEGCOMPLETE ; 
 int /*<<< orphan*/  MII_BMSR ; 
 scalar_t__ PHY_AUTO_NEG_LIMIT ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static s32 e1000_wait_autoneg(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	u16 i, phy_status;

	/* Break after autoneg completes or PHY_AUTO_NEG_LIMIT expires. */
	for (i = PHY_AUTO_NEG_LIMIT; i > 0; i--) {
		ret_val = e1e_rphy(hw, MII_BMSR, &phy_status);
		if (ret_val)
			break;
		ret_val = e1e_rphy(hw, MII_BMSR, &phy_status);
		if (ret_val)
			break;
		if (phy_status & BMSR_ANEGCOMPLETE)
			break;
		msleep(100);
	}

	/* PHY_AUTO_NEG_TIME expiration doesn't guarantee auto-negotiation
	 * has completed.
	 */
	return ret_val;
}