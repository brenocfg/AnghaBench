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
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MSCC_EXT_PAGE_ACCESS ; 
 int /*<<< orphan*/  MSCC_EXT_PAGE_CSR_CNTL_17 ; 
 int /*<<< orphan*/  MSCC_EXT_PAGE_CSR_CNTL_18 ; 
 int /*<<< orphan*/  MSCC_EXT_PAGE_CSR_CNTL_19 ; 
 int /*<<< orphan*/  MSCC_EXT_PAGE_CSR_CNTL_20 ; 
 int MSCC_PHY_CSR_CNTL_19_CMD ; 
 int MSCC_PHY_CSR_CNTL_19_REG_ADDR (int) ; 
 int MSCC_PHY_CSR_CNTL_19_TARGET (int) ; 
 int MSCC_PHY_CSR_CNTL_20_TARGET (int) ; 
 int MSCC_PHY_PAGE_CSR_CNTL ; 
 int MSCC_PHY_PAGE_STANDARD ; 
 int /*<<< orphan*/  PROC_CMD_NCOMPLETED_TIMEOUT_MS ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int phy_base_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_base_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int vsc85xx_csr_ctrl_phy_write(struct phy_device *phydev,
				      u32 target, u32 reg, u32 val)
{
	unsigned long deadline;

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_CSR_CNTL);

	/* CSR registers are grouped under different Target IDs.
	 * 6-bit Target_ID is split between MSCC_EXT_PAGE_CSR_CNTL_20 and
	 * MSCC_EXT_PAGE_CSR_CNTL_19 registers.
	 * Target_ID[5:2] maps to bits[3:0] of MSCC_EXT_PAGE_CSR_CNTL_20
	 * and Target_ID[1:0] maps to bits[13:12] of MSCC_EXT_PAGE_CSR_CNTL_19.
	 */

	/* Setup the Target ID */
	phy_base_write(phydev, MSCC_EXT_PAGE_CSR_CNTL_20,
		       MSCC_PHY_CSR_CNTL_20_TARGET(target >> 2));

	/* Write the Least Significant Word (LSW) (17) */
	phy_base_write(phydev, MSCC_EXT_PAGE_CSR_CNTL_17, (u16)val);

	/* Write the Most Significant Word (MSW) (18) */
	phy_base_write(phydev, MSCC_EXT_PAGE_CSR_CNTL_18, (u16)(val >> 16));

	/* Trigger CSR Action - Write into the CSR's */
	phy_base_write(phydev, MSCC_EXT_PAGE_CSR_CNTL_19,
		       MSCC_PHY_CSR_CNTL_19_CMD |
		       MSCC_PHY_CSR_CNTL_19_REG_ADDR(reg) |
		       MSCC_PHY_CSR_CNTL_19_TARGET(target & 0x3));

	/* Wait for register access */
	deadline = jiffies + msecs_to_jiffies(PROC_CMD_NCOMPLETED_TIMEOUT_MS);
	do {
		usleep_range(500, 1000);
		val = phy_base_read(phydev, MSCC_EXT_PAGE_CSR_CNTL_19);
	} while (time_before(jiffies, deadline) &&
		 !(val & MSCC_PHY_CSR_CNTL_19_CMD));

	if (!(val & MSCC_PHY_CSR_CNTL_19_CMD))
		return -ETIMEDOUT;

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_STANDARD);

	return 0;
}