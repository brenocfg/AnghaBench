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
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MSCC_EXT_PAGE_ACCESS ; 
 int MSCC_PHY_PAGE_EXTENDED_GPIO ; 
 int MSCC_PHY_PAGE_STANDARD ; 
 int /*<<< orphan*/  MSCC_PHY_PROC_CMD ; 
 int PROC_CMD_FAILED ; 
 int PROC_CMD_NCOMPLETED ; 
 int /*<<< orphan*/  PROC_CMD_NCOMPLETED_TIMEOUT_MS ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int phy_base_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_base_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int vsc8584_cmd(struct phy_device *phydev, u16 val)
{
	unsigned long deadline;
	u16 reg_val;

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	phy_base_write(phydev, MSCC_PHY_PROC_CMD, PROC_CMD_NCOMPLETED | val);

	deadline = jiffies + msecs_to_jiffies(PROC_CMD_NCOMPLETED_TIMEOUT_MS);
	do {
		reg_val = phy_base_read(phydev, MSCC_PHY_PROC_CMD);
	} while (time_before(jiffies, deadline) &&
		 (reg_val & PROC_CMD_NCOMPLETED) &&
		 !(reg_val & PROC_CMD_FAILED));

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	if (reg_val & PROC_CMD_FAILED)
		return -EIO;

	if (reg_val & PROC_CMD_NCOMPLETED)
		return -ETIMEDOUT;

	return 0;
}