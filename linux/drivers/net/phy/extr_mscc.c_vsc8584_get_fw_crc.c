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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSCC_EXT_PAGE_ACCESS ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_STANDARD ; 
 int /*<<< orphan*/  MSCC_PHY_VERIPHY_CNTL_2 ; 
 int /*<<< orphan*/  MSCC_PHY_VERIPHY_CNTL_3 ; 
 int /*<<< orphan*/  PROC_CMD_CRC16 ; 
 int /*<<< orphan*/  phy_base_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_base_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vsc8584_cmd (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc8584_get_fw_crc(struct phy_device *phydev, u16 start, u16 size,
			      u16 *crc)
{
	int ret;

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED);

	phy_base_write(phydev, MSCC_PHY_VERIPHY_CNTL_2, start);
	phy_base_write(phydev, MSCC_PHY_VERIPHY_CNTL_3, size);

	/* Start Micro command */
	ret = vsc8584_cmd(phydev, PROC_CMD_CRC16);
	if (ret)
		goto out;

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED);

	*crc = phy_base_read(phydev, MSCC_PHY_VERIPHY_CNTL_2);

out:
	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	return ret;
}