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
struct mii_bus {int phy_ignore_ta_mask; struct mdiobb_ctrl* priv; } ;
struct mdiobb_ctrl {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_mdio_dir ) (struct mdiobb_ctrl*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_C45_READ ; 
 int /*<<< orphan*/  MDIO_READ ; 
 int MII_ADDR_C45 ; 
 int /*<<< orphan*/  mdiobb_cmd (struct mdiobb_ctrl*,int /*<<< orphan*/ ,int,int) ; 
 int mdiobb_cmd_addr (struct mdiobb_ctrl*,int,int) ; 
 scalar_t__ mdiobb_get_bit (struct mdiobb_ctrl*) ; 
 int mdiobb_get_num (struct mdiobb_ctrl*,int) ; 
 int /*<<< orphan*/  stub1 (struct mdiobb_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdiobb_read(struct mii_bus *bus, int phy, int reg)
{
	struct mdiobb_ctrl *ctrl = bus->priv;
	int ret, i;

	if (reg & MII_ADDR_C45) {
		reg = mdiobb_cmd_addr(ctrl, phy, reg);
		mdiobb_cmd(ctrl, MDIO_C45_READ, phy, reg);
	} else
		mdiobb_cmd(ctrl, MDIO_READ, phy, reg);

	ctrl->ops->set_mdio_dir(ctrl, 0);

	/* check the turnaround bit: the PHY should be driving it to zero, if this
	 * PHY is listed in phy_ignore_ta_mask as having broken TA, skip that
	 */
	if (mdiobb_get_bit(ctrl) != 0 &&
	    !(bus->phy_ignore_ta_mask & (1 << phy))) {
		/* PHY didn't drive TA low -- flush any bits it
		 * may be trying to send.
		 */
		for (i = 0; i < 32; i++)
			mdiobb_get_bit(ctrl);

		return 0xffff;
	}

	ret = mdiobb_get_num(ctrl, 16);
	mdiobb_get_bit(ctrl);
	return ret;
}