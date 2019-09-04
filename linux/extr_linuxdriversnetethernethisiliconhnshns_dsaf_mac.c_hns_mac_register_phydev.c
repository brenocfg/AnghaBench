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
typedef  size_t u32 ;
struct phy_device {int /*<<< orphan*/  irq; } ;
struct mii_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/ * irq; } ;
struct hns_mac_cb {struct phy_device* phy_dev; int /*<<< orphan*/  fw_port; } ;

/* Variables and functions */
 int EIO ; 
 int ENODATA ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_XGMII ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 int fwnode_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 struct phy_device* get_phy_device (struct mii_bus*,size_t,int) ; 
 int /*<<< orphan*/  phy_device_free (struct phy_device*) ; 
 int phy_device_register (struct phy_device*) ; 
 int /*<<< orphan*/  phy_modes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hns_mac_register_phydev(struct mii_bus *mdio, struct hns_mac_cb *mac_cb,
			u32 addr)
{
	struct phy_device *phy;
	const char *phy_type;
	bool is_c45;
	int rc;

	rc = fwnode_property_read_string(mac_cb->fw_port,
					 "phy-mode", &phy_type);
	if (rc < 0)
		return rc;

	if (!strcmp(phy_type, phy_modes(PHY_INTERFACE_MODE_XGMII)))
		is_c45 = 1;
	else if (!strcmp(phy_type, phy_modes(PHY_INTERFACE_MODE_SGMII)))
		is_c45 = 0;
	else
		return -ENODATA;

	phy = get_phy_device(mdio, addr, is_c45);
	if (!phy || IS_ERR(phy))
		return -EIO;

	phy->irq = mdio->irq[addr];

	/* All data is now stored in the phy struct;
	 * register it
	 */
	rc = phy_device_register(phy);
	if (rc) {
		phy_device_free(phy);
		dev_err(&mdio->dev, "registered phy fail at address %i\n",
			addr);
		return -ENODEV;
	}

	mac_cb->phy_dev = phy;

	dev_dbg(&mdio->dev, "registered phy at address %i\n", addr);

	return 0;
}