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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct atl1c_hw {int media_type; int phy_configured; int /*<<< orphan*/  phy_id2; int /*<<< orphan*/  phy_id1; struct atl1c_adapter* adapter; } ;
struct atl1c_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_RESET ; 
 int BMCR_SPEED100 ; 
#define  MEDIA_TYPE_100M_FULL 132 
#define  MEDIA_TYPE_100M_HALF 131 
#define  MEDIA_TYPE_10M_FULL 130 
#define  MEDIA_TYPE_10M_HALF 129 
#define  MEDIA_TYPE_AUTO_SENSOR 128 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_PHYSID1 ; 
 int /*<<< orphan*/  MII_PHYSID2 ; 
 int atl1c_phy_setup_adv (struct atl1c_hw*) ; 
 scalar_t__ atl1c_read_phy_reg (struct atl1c_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atl1c_write_phy_reg (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  netif_msg_link (struct atl1c_adapter*) ; 

int atl1c_phy_init(struct atl1c_hw *hw)
{
	struct atl1c_adapter *adapter = hw->adapter;
	struct pci_dev *pdev = adapter->pdev;
	int ret_val;
	u16 mii_bmcr_data = BMCR_RESET;

	if ((atl1c_read_phy_reg(hw, MII_PHYSID1, &hw->phy_id1) != 0) ||
		(atl1c_read_phy_reg(hw, MII_PHYSID2, &hw->phy_id2) != 0)) {
		dev_err(&pdev->dev, "Error get phy ID\n");
		return -1;
	}
	switch (hw->media_type) {
	case MEDIA_TYPE_AUTO_SENSOR:
		ret_val = atl1c_phy_setup_adv(hw);
		if (ret_val) {
			if (netif_msg_link(adapter))
				dev_err(&pdev->dev,
					"Error Setting up Auto-Negotiation\n");
			return ret_val;
		}
		mii_bmcr_data |= BMCR_ANENABLE | BMCR_ANRESTART;
		break;
	case MEDIA_TYPE_100M_FULL:
		mii_bmcr_data |= BMCR_SPEED100 | BMCR_FULLDPLX;
		break;
	case MEDIA_TYPE_100M_HALF:
		mii_bmcr_data |= BMCR_SPEED100;
		break;
	case MEDIA_TYPE_10M_FULL:
		mii_bmcr_data |= BMCR_FULLDPLX;
		break;
	case MEDIA_TYPE_10M_HALF:
		break;
	default:
		if (netif_msg_link(adapter))
			dev_err(&pdev->dev, "Wrong Media type %d\n",
				hw->media_type);
		return -1;
	}

	ret_val = atl1c_write_phy_reg(hw, MII_BMCR, mii_bmcr_data);
	if (ret_val)
		return ret_val;
	hw->phy_configured = true;

	return 0;
}