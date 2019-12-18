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
struct realtek_smi {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTL8366RB_PHY_ACCESS_CTRL_REG ; 
 int /*<<< orphan*/  RTL8366RB_PHY_ACCESS_DATA_REG ; 
 int /*<<< orphan*/  RTL8366RB_PHY_CTRL_READ ; 
 int RTL8366RB_PHY_NO_MAX ; 
 int RTL8366RB_PHY_NO_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8366rb_phy_read(struct realtek_smi *smi, int phy, int regnum)
{
	u32 val;
	u32 reg;
	int ret;

	if (phy > RTL8366RB_PHY_NO_MAX)
		return -EINVAL;

	ret = regmap_write(smi->map, RTL8366RB_PHY_ACCESS_CTRL_REG,
			   RTL8366RB_PHY_CTRL_READ);
	if (ret)
		return ret;

	reg = 0x8000 | (1 << (phy + RTL8366RB_PHY_NO_OFFSET)) | regnum;

	ret = regmap_write(smi->map, reg, 0);
	if (ret) {
		dev_err(smi->dev,
			"failed to write PHY%d reg %04x @ %04x, ret %d\n",
			phy, regnum, reg, ret);
		return ret;
	}

	ret = regmap_read(smi->map, RTL8366RB_PHY_ACCESS_DATA_REG, &val);
	if (ret)
		return ret;

	dev_dbg(smi->dev, "read PHY%d register 0x%04x @ %08x, val <- %04x\n",
		phy, regnum, reg, val);

	return val;
}