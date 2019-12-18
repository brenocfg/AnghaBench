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
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int DW8051_CLK_EN ; 
 int EN_PATCH_RAM_TRAP_ADDR (int) ; 
 int MICRO_CLK_EN ; 
 int MICRO_NSOFT_RESET ; 
 int /*<<< orphan*/  MSCC_DW8051_CNTL_STATUS ; 
 int MSCC_DW8051_VLD_MASK ; 
 int /*<<< orphan*/  MSCC_EXT_PAGE_ACCESS ; 
 int /*<<< orphan*/  MSCC_INT_MEM_CNTL ; 
 int /*<<< orphan*/  MSCC_PATCH_RAM_ADDR (int) ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED_GPIO ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_STANDARD ; 
 int /*<<< orphan*/  MSCC_TRAP_ROM_ADDR (int) ; 
 int RUN_FROM_INT_ROM ; 
 int phy_base_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_base_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vsc8574_is_serdes_init(struct phy_device *phydev)
{
	u16 reg;
	bool ret;

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	reg = phy_base_read(phydev, MSCC_TRAP_ROM_ADDR(1));
	if (reg != 0x3eb7) {
		ret = false;
		goto out;
	}

	reg = phy_base_read(phydev, MSCC_PATCH_RAM_ADDR(1));
	if (reg != 0x4012) {
		ret = false;
		goto out;
	}

	reg = phy_base_read(phydev, MSCC_INT_MEM_CNTL);
	if (reg != EN_PATCH_RAM_TRAP_ADDR(1)) {
		ret = false;
		goto out;
	}

	reg = phy_base_read(phydev, MSCC_DW8051_CNTL_STATUS);
	if ((MICRO_NSOFT_RESET | RUN_FROM_INT_ROM |  DW8051_CLK_EN |
	     MICRO_CLK_EN) != (reg & MSCC_DW8051_VLD_MASK)) {
		ret = false;
		goto out;
	}

	ret = true;
out:
	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	return ret;
}