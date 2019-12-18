#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lan9303 {int phy_addr_base; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* phy_read ) (struct lan9303*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MII_LAN911X_SPECIAL_MODES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct lan9303*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_detect_phy_setup(struct lan9303 *chip)
{
	int reg;

	/* Calculate chip->phy_addr_base:
	 * Depending on the 'phy_addr_sel_strap' setting, the three phys are
	 * using IDs 0-1-2 or IDs 1-2-3. We cannot read back the
	 * 'phy_addr_sel_strap' setting directly, so we need a test, which
	 * configuration is active:
	 * Special reg 18 of phy 3 reads as 0x0000, if 'phy_addr_sel_strap' is 0
	 * and the IDs are 0-1-2, else it contains something different from
	 * 0x0000, which means 'phy_addr_sel_strap' is 1 and the IDs are 1-2-3.
	 * 0xffff is returned on MDIO read with no response.
	 */
	reg = chip->ops->phy_read(chip, 3, MII_LAN911X_SPECIAL_MODES);
	if (reg < 0) {
		dev_err(chip->dev, "Failed to detect phy config: %d\n", reg);
		return reg;
	}

	chip->phy_addr_base = reg != 0 && reg != 0xffff;

	dev_dbg(chip->dev, "Phy setup '%s' detected\n",
		chip->phy_addr_base ? "1-2-3" : "0-1-2");

	return 0;
}