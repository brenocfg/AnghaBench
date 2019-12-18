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
struct vsc73xx {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct vsc73xx* priv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_MII ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int vsc73xx_write (struct vsc73xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vsc73xx_phy_write(struct dsa_switch *ds, int phy, int regnum,
			     u16 val)
{
	struct vsc73xx *vsc = ds->priv;
	u32 cmd;
	int ret;

	/* It was found through tedious experiments that this router
	 * chip really hates to have it's PHYs reset. They
	 * never recover if that happens: autonegotiation stops
	 * working after a reset. Just filter out this command.
	 * (Resetting the whole chip is OK.)
	 */
	if (regnum == 0 && (val & BIT(15))) {
		dev_info(vsc->dev, "reset PHY - disallowed\n");
		return 0;
	}

	cmd = (phy << 21) | (regnum << 16);
	ret = vsc73xx_write(vsc, VSC73XX_BLOCK_MII, 0, 1, cmd);
	if (ret)
		return ret;

	dev_dbg(vsc->dev, "write %04x to reg %02x in phy%d\n",
		val, regnum, phy);
	return 0;
}