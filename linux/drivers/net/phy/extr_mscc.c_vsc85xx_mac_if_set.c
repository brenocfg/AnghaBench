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
struct phy_device {int /*<<< orphan*/  lock; } ;
typedef  int phy_interface_t ;

/* Variables and functions */
 int EINVAL ; 
 int MAC_IF_SELECTION_GMII ; 
 int MAC_IF_SELECTION_MASK ; 
 int MAC_IF_SELECTION_POS ; 
 int MAC_IF_SELECTION_RGMII ; 
 int MAC_IF_SELECTION_RMII ; 
 int /*<<< orphan*/  MSCC_PHY_EXT_PHY_CNTL_1 ; 
#define  PHY_INTERFACE_MODE_GMII 131 
#define  PHY_INTERFACE_MODE_MII 130 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int genphy_soft_reset (struct phy_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vsc85xx_mac_if_set(struct phy_device *phydev,
			      phy_interface_t interface)
{
	int rc;
	u16 reg_val;

	mutex_lock(&phydev->lock);
	reg_val = phy_read(phydev, MSCC_PHY_EXT_PHY_CNTL_1);
	reg_val &= ~(MAC_IF_SELECTION_MASK);
	switch (interface) {
	case PHY_INTERFACE_MODE_RGMII:
		reg_val |= (MAC_IF_SELECTION_RGMII << MAC_IF_SELECTION_POS);
		break;
	case PHY_INTERFACE_MODE_RMII:
		reg_val |= (MAC_IF_SELECTION_RMII << MAC_IF_SELECTION_POS);
		break;
	case PHY_INTERFACE_MODE_MII:
	case PHY_INTERFACE_MODE_GMII:
		reg_val |= (MAC_IF_SELECTION_GMII << MAC_IF_SELECTION_POS);
		break;
	default:
		rc = -EINVAL;
		goto out_unlock;
	}
	rc = phy_write(phydev, MSCC_PHY_EXT_PHY_CNTL_1, reg_val);
	if (rc)
		goto out_unlock;

	rc = genphy_soft_reset(phydev);

out_unlock:
	mutex_unlock(&phydev->lock);

	return rc;
}