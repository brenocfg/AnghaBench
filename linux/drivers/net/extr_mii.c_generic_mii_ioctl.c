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
struct mii_ioctl_data {int reg_num; int val_in; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  val_out; } ;
struct mii_if_info {int reg_num_mask; int force_media; unsigned int full_duplex; int advertising; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* mdio_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  phy_id; int /*<<< orphan*/  (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  phy_id_mask; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_RESET ; 
 int EOPNOTSUPP ; 
#define  MII_ADVERTISE 132 
#define  MII_BMCR 131 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int generic_mii_ioctl(struct mii_if_info *mii_if,
		      struct mii_ioctl_data *mii_data, int cmd,
		      unsigned int *duplex_chg_out)
{
	int rc = 0;
	unsigned int duplex_changed = 0;

	if (duplex_chg_out)
		*duplex_chg_out = 0;

	mii_data->phy_id &= mii_if->phy_id_mask;
	mii_data->reg_num &= mii_if->reg_num_mask;

	switch(cmd) {
	case SIOCGMIIPHY:
		mii_data->phy_id = mii_if->phy_id;
		/* fall through */

	case SIOCGMIIREG:
		mii_data->val_out =
			mii_if->mdio_read(mii_if->dev, mii_data->phy_id,
					  mii_data->reg_num);
		break;

	case SIOCSMIIREG: {
		u16 val = mii_data->val_in;

		if (mii_data->phy_id == mii_if->phy_id) {
			switch(mii_data->reg_num) {
			case MII_BMCR: {
				unsigned int new_duplex = 0;
				if (val & (BMCR_RESET|BMCR_ANENABLE))
					mii_if->force_media = 0;
				else
					mii_if->force_media = 1;
				if (mii_if->force_media &&
				    (val & BMCR_FULLDPLX))
					new_duplex = 1;
				if (mii_if->full_duplex != new_duplex) {
					duplex_changed = 1;
					mii_if->full_duplex = new_duplex;
				}
				break;
			}
			case MII_ADVERTISE:
				mii_if->advertising = val;
				break;
			default:
				/* do nothing */
				break;
			}
		}

		mii_if->mdio_write(mii_if->dev, mii_data->phy_id,
				   mii_data->reg_num, val);
		break;
	}

	default:
		rc = -EOPNOTSUPP;
		break;
	}

	if ((rc == 0) && (duplex_chg_out) && (duplex_changed))
		*duplex_chg_out = 1;

	return rc;
}