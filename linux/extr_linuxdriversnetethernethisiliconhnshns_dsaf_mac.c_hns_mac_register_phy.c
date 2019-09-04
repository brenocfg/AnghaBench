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
struct platform_device {int dummy; } ;
struct mii_bus {int dummy; } ;
struct hns_mac_cb {int /*<<< orphan*/  mac_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  fw_port; } ;
struct fwnode_reference_args {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int acpi_node_get_property_reference (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct fwnode_reference_args*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct platform_device* hns_dsaf_find_platform_device (int /*<<< orphan*/ ) ; 
 int hns_mac_phy_parse_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hns_mac_register_phydev (struct mii_bus*,struct hns_mac_cb*,int) ; 
 int /*<<< orphan*/  is_acpi_device_node (int /*<<< orphan*/ ) ; 
 struct mii_bus* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  to_acpi_device_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_mac_register_phy(struct hns_mac_cb *mac_cb)
{
	struct fwnode_reference_args args;
	struct platform_device *pdev;
	struct mii_bus *mii_bus;
	int rc;
	int addr;

	/* Loop over the child nodes and register a phy_device for each one */
	if (!to_acpi_device_node(mac_cb->fw_port))
		return -ENODEV;

	rc = acpi_node_get_property_reference(
			mac_cb->fw_port, "mdio-node", 0, &args);
	if (rc)
		return rc;
	if (!is_acpi_device_node(args.fwnode))
		return -EINVAL;

	addr = hns_mac_phy_parse_addr(mac_cb->dev, mac_cb->fw_port);
	if (addr < 0)
		return addr;

	/* dev address in adev */
	pdev = hns_dsaf_find_platform_device(args.fwnode);
	if (!pdev) {
		dev_err(mac_cb->dev, "mac%d mdio pdev is NULL\n",
			mac_cb->mac_id);
		return  -EINVAL;
	}

	mii_bus = platform_get_drvdata(pdev);
	if (!mii_bus) {
		dev_err(mac_cb->dev,
			"mac%d mdio is NULL, dsaf will probe again later\n",
			mac_cb->mac_id);
		return -EPROBE_DEFER;
	}

	rc = hns_mac_register_phydev(mii_bus, mac_cb, addr);
	if (!rc)
		dev_dbg(mac_cb->dev, "mac%d register phy addr:%d\n",
			mac_cb->mac_id, addr);

	return rc;
}