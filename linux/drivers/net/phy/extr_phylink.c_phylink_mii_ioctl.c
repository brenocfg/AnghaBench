#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phylink {TYPE_2__* phydev; } ;
struct mii_ioctl_data {int val_out; int /*<<< orphan*/  val_in; int /*<<< orphan*/  reg_num; int /*<<< orphan*/  phy_id; } ;
struct ifreq {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int phy_mii_ioctl (TYPE_2__*,struct ifreq*,int) ; 
 int phylink_mii_read (struct phylink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phylink_mii_write (struct phylink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phylink_phy_read (struct phylink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phylink_phy_write (struct phylink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int phylink_mii_ioctl(struct phylink *pl, struct ifreq *ifr, int cmd)
{
	struct mii_ioctl_data *mii = if_mii(ifr);
	int  ret;

	ASSERT_RTNL();

	if (pl->phydev) {
		/* PHYs only exist for MLO_AN_PHY and SGMII */
		switch (cmd) {
		case SIOCGMIIPHY:
			mii->phy_id = pl->phydev->mdio.addr;
			/* fall through */

		case SIOCGMIIREG:
			ret = phylink_phy_read(pl, mii->phy_id, mii->reg_num);
			if (ret >= 0) {
				mii->val_out = ret;
				ret = 0;
			}
			break;

		case SIOCSMIIREG:
			ret = phylink_phy_write(pl, mii->phy_id, mii->reg_num,
						mii->val_in);
			break;

		default:
			ret = phy_mii_ioctl(pl->phydev, ifr, cmd);
			break;
		}
	} else {
		switch (cmd) {
		case SIOCGMIIPHY:
			mii->phy_id = 0;
			/* fall through */

		case SIOCGMIIREG:
			ret = phylink_mii_read(pl, mii->phy_id, mii->reg_num);
			if (ret >= 0) {
				mii->val_out = ret;
				ret = 0;
			}
			break;

		case SIOCSMIIREG:
			ret = phylink_mii_write(pl, mii->phy_id, mii->reg_num,
						mii->val_in);
			break;

		default:
			ret = -EOPNOTSUPP;
			break;
		}
	}

	return ret;
}