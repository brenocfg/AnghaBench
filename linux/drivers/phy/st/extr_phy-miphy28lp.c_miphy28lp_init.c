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
struct phy {int dummy; } ;
struct miphy28lp_phy {int type; struct miphy28lp_dev* phydev; } ;
struct miphy28lp_dev {int /*<<< orphan*/  miphy_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_TYPE_PCIE 130 
#define  PHY_TYPE_SATA 129 
#define  PHY_TYPE_USB3 128 
 int miphy28lp_init_pcie (struct miphy28lp_phy*) ; 
 int miphy28lp_init_sata (struct miphy28lp_phy*) ; 
 int miphy28lp_init_usb3 (struct miphy28lp_phy*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct miphy28lp_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int miphy28lp_init(struct phy *phy)
{
	struct miphy28lp_phy *miphy_phy = phy_get_drvdata(phy);
	struct miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	int ret;

	mutex_lock(&miphy_dev->miphy_mutex);

	switch (miphy_phy->type) {

	case PHY_TYPE_SATA:
		ret = miphy28lp_init_sata(miphy_phy);
		break;
	case PHY_TYPE_PCIE:
		ret = miphy28lp_init_pcie(miphy_phy);
		break;
	case PHY_TYPE_USB3:
		ret = miphy28lp_init_usb3(miphy_phy);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&miphy_dev->miphy_mutex);

	return ret;
}