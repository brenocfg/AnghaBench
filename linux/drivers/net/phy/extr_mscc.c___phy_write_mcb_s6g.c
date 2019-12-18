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
typedef  int u8 ;
typedef  int u32 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PHY_MCB_TARGET ; 
 int /*<<< orphan*/  PROC_CMD_NCOMPLETED_TIMEOUT_MS ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int vsc85xx_csr_ctrl_phy_read (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int vsc85xx_csr_ctrl_phy_write (struct phy_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int __phy_write_mcb_s6g(struct phy_device *phydev, u32 reg, u8 mcb,
			       u32 op)
{
	unsigned long deadline;
	u32 val;
	int ret;

	ret = vsc85xx_csr_ctrl_phy_write(phydev, PHY_MCB_TARGET, reg,
					 op | (1 << mcb));
	if (ret)
		return -EINVAL;

	deadline = jiffies + msecs_to_jiffies(PROC_CMD_NCOMPLETED_TIMEOUT_MS);
	do {
		usleep_range(500, 1000);
		val = vsc85xx_csr_ctrl_phy_read(phydev, PHY_MCB_TARGET, reg);

		if (val == 0xffffffff)
			return -EIO;

	} while (time_before(jiffies, deadline) && (val & op));

	if (val & op)
		return -ETIMEDOUT;

	return 0;
}