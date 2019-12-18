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
typedef  char u16 ;
struct ixgb_hw {int dummy; } ;
typedef  int /*<<< orphan*/  ixgb_xpak_vendor ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  IXGB_PHY_ADDRESS ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 scalar_t__ MDIO_PMA_PMD_XPAK_VENDOR_NAME ; 
 char ixgb_read_phy_reg (struct ixgb_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_xpak_vendor_infineon ; 
 int /*<<< orphan*/  ixgb_xpak_vendor_intel ; 

__attribute__((used)) static ixgb_xpak_vendor
ixgb_identify_xpak_vendor(struct ixgb_hw *hw)
{
	u32 i;
	u16 vendor_name[5];
	ixgb_xpak_vendor xpak_vendor;

	ENTER();

	/* Read the first few bytes of the vendor string from the XPAK NVR
	 * registers.  These are standard XENPAK/XPAK registers, so all XPAK
	 * devices should implement them. */
	for (i = 0; i < 5; i++) {
		vendor_name[i] = ixgb_read_phy_reg(hw,
						   MDIO_PMA_PMD_XPAK_VENDOR_NAME
						   + i, IXGB_PHY_ADDRESS,
						   MDIO_MMD_PMAPMD);
	}

	/* Determine the actual vendor */
	if (vendor_name[0] == 'I' &&
	    vendor_name[1] == 'N' &&
	    vendor_name[2] == 'T' &&
	    vendor_name[3] == 'E' && vendor_name[4] == 'L') {
		xpak_vendor = ixgb_xpak_vendor_intel;
	} else {
		xpak_vendor = ixgb_xpak_vendor_infineon;
	}

	return xpak_vendor;
}