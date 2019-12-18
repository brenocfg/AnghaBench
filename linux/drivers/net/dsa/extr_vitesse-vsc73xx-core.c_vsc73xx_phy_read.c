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
struct vsc73xx {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct vsc73xx* priv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_MII ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int vsc73xx_read (struct vsc73xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int vsc73xx_write (struct vsc73xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vsc73xx_phy_read(struct dsa_switch *ds, int phy, int regnum)
{
	struct vsc73xx *vsc = ds->priv;
	u32 cmd;
	u32 val;
	int ret;

	/* Setting bit 26 means "read" */
	cmd = BIT(26) | (phy << 21) | (regnum << 16);
	ret = vsc73xx_write(vsc, VSC73XX_BLOCK_MII, 0, 1, cmd);
	if (ret)
		return ret;
	msleep(2);
	ret = vsc73xx_read(vsc, VSC73XX_BLOCK_MII, 0, 2, &val);
	if (ret)
		return ret;
	if (val & BIT(16)) {
		dev_err(vsc->dev, "reading reg %02x from phy%d failed\n",
			regnum, phy);
		return -EIO;
	}
	val &= 0xFFFFU;

	dev_dbg(vsc->dev, "read reg %02x from phy%d = %04x\n",
		regnum, phy, val);

	return val;
}