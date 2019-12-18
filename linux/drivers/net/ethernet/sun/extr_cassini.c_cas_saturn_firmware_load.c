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
struct cas {int* fw_data; int fw_load_addr; int fw_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP83065_MII_MEM ; 
 int /*<<< orphan*/  DP83065_MII_REGD ; 
 int /*<<< orphan*/  DP83065_MII_REGE ; 
 int /*<<< orphan*/  cas_phy_powerdown (struct cas*) ; 
 int /*<<< orphan*/  cas_phy_write (struct cas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cas_saturn_firmware_load(struct cas *cp)
{
	int i;

	if (!cp->fw_data)
		return;

	cas_phy_powerdown(cp);

	/* expanded memory access mode */
	cas_phy_write(cp, DP83065_MII_MEM, 0x0);

	/* pointer configuration for new firmware */
	cas_phy_write(cp, DP83065_MII_REGE, 0x8ff9);
	cas_phy_write(cp, DP83065_MII_REGD, 0xbd);
	cas_phy_write(cp, DP83065_MII_REGE, 0x8ffa);
	cas_phy_write(cp, DP83065_MII_REGD, 0x82);
	cas_phy_write(cp, DP83065_MII_REGE, 0x8ffb);
	cas_phy_write(cp, DP83065_MII_REGD, 0x0);
	cas_phy_write(cp, DP83065_MII_REGE, 0x8ffc);
	cas_phy_write(cp, DP83065_MII_REGD, 0x39);

	/* download new firmware */
	cas_phy_write(cp, DP83065_MII_MEM, 0x1);
	cas_phy_write(cp, DP83065_MII_REGE, cp->fw_load_addr);
	for (i = 0; i < cp->fw_size; i++)
		cas_phy_write(cp, DP83065_MII_REGD, cp->fw_data[i]);

	/* enable firmware */
	cas_phy_write(cp, DP83065_MII_REGE, 0x8ff8);
	cas_phy_write(cp, DP83065_MII_REGD, 0x1);
}