#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regmap {int dummy; } ;
struct of_phandle_args {int /*<<< orphan*/ * args; struct device_node* np; } ;
struct hns_mac_cb {int link; int half_duplex; size_t phy_if; int /*<<< orphan*/  mc_mask; TYPE_4__* dev; int /*<<< orphan*/  fw_port; int /*<<< orphan*/  media_type; scalar_t__ mac_id; int /*<<< orphan*/  cpld_ctrl_reg; struct regmap* cpld_ctrl; scalar_t__ port_mode_off; scalar_t__ port_rst_off; struct regmap* serdes_ctrl; TYPE_2__* phy_dev; int /*<<< orphan*/  tx_pause_frm_time; int /*<<< orphan*/  max_frm; int /*<<< orphan*/  if_support; int /*<<< orphan*/  speed; int /*<<< orphan*/  max_speed; } ;
struct device_node {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {TYPE_1__ mdio; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HNAE_MEDIA_TYPE_UNKNOWN ; 
 scalar_t__ IS_ERR_OR_NULL (struct regmap*) ; 
 int /*<<< orphan*/  MAC_DEFAULT_MTU ; 
 int /*<<< orphan*/  MAC_DEFAULT_PAUSE_TIME ; 
 int /*<<< orphan*/  MAC_GMAC_SUPPORTED ; 
 int /*<<< orphan*/  MAC_MEDIA_TYPE_MAX_LEN ; 
 size_t PHY_INTERFACE_MODE_SGMII ; 
 size_t PHY_INTERFACE_MODE_XGMII ; 
 int /*<<< orphan*/  SUPPORTED_10000baseKR_Full ; 
 int /*<<< orphan*/  SUPPORTED_10000baseR_FEC ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Full ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnode_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 int fwnode_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 scalar_t__ fwnode_property_read_u8_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hns_mac_register_phy (struct hns_mac_cb*) ; 
 scalar_t__ is_acpi_node (int /*<<< orphan*/ ) ; 
 scalar_t__ is_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mac_phy_to_speed ; 
 TYPE_3__* media_type_defs ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int of_parse_phandle_with_fixed_args (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 void* of_phy_find_device (struct device_node*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 
 int /*<<< orphan*/  to_of_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_mac_get_info(struct hns_mac_cb *mac_cb)
{
	struct device_node *np;
	struct regmap *syscon;
	struct of_phandle_args cpld_args;
	const char *media_type;
	u32 i;
	u32 ret;

	mac_cb->link = false;
	mac_cb->half_duplex = false;
	mac_cb->media_type = HNAE_MEDIA_TYPE_UNKNOWN;
	mac_cb->speed = mac_phy_to_speed[mac_cb->phy_if];
	mac_cb->max_speed = mac_cb->speed;

	if (mac_cb->phy_if == PHY_INTERFACE_MODE_SGMII) {
		mac_cb->if_support = MAC_GMAC_SUPPORTED;
		mac_cb->if_support |= SUPPORTED_1000baseT_Full;
	} else if (mac_cb->phy_if == PHY_INTERFACE_MODE_XGMII) {
		mac_cb->if_support = SUPPORTED_10000baseR_FEC;
		mac_cb->if_support |= SUPPORTED_10000baseKR_Full;
	}

	mac_cb->max_frm = MAC_DEFAULT_MTU;
	mac_cb->tx_pause_frm_time = MAC_DEFAULT_PAUSE_TIME;
	mac_cb->port_rst_off = mac_cb->mac_id;
	mac_cb->port_mode_off = 0;

	/* if the dsaf node doesn't contain a port subnode, get phy-handle
	 * from dsaf node
	 */
	if (!mac_cb->fw_port) {
		np = of_parse_phandle(mac_cb->dev->of_node, "phy-handle",
				      mac_cb->mac_id);
		mac_cb->phy_dev = of_phy_find_device(np);
		if (mac_cb->phy_dev) {
			/* refcount is held by of_phy_find_device()
			 * if the phy_dev is found
			 */
			put_device(&mac_cb->phy_dev->mdio.dev);

			dev_dbg(mac_cb->dev, "mac%d phy_node: %pOFn\n",
				mac_cb->mac_id, np);
		}
		of_node_put(np);

		return 0;
	}

	if (is_of_node(mac_cb->fw_port)) {
		/* parse property from port subnode in dsaf */
		np = of_parse_phandle(to_of_node(mac_cb->fw_port),
				      "phy-handle", 0);
		mac_cb->phy_dev = of_phy_find_device(np);
		if (mac_cb->phy_dev) {
			/* refcount is held by of_phy_find_device()
			 * if the phy_dev is found
			 */
			put_device(&mac_cb->phy_dev->mdio.dev);
			dev_dbg(mac_cb->dev, "mac%d phy_node: %pOFn\n",
				mac_cb->mac_id, np);
		}
		of_node_put(np);

		np = of_parse_phandle(to_of_node(mac_cb->fw_port),
				      "serdes-syscon", 0);
		syscon = syscon_node_to_regmap(np);
		of_node_put(np);
		if (IS_ERR_OR_NULL(syscon)) {
			dev_err(mac_cb->dev, "serdes-syscon is needed!\n");
			return -EINVAL;
		}
		mac_cb->serdes_ctrl = syscon;

		ret = fwnode_property_read_u32(mac_cb->fw_port,
					       "port-rst-offset",
					       &mac_cb->port_rst_off);
		if (ret) {
			dev_dbg(mac_cb->dev,
				"mac%d port-rst-offset not found, use default value.\n",
				mac_cb->mac_id);
		}

		ret = fwnode_property_read_u32(mac_cb->fw_port,
					       "port-mode-offset",
					       &mac_cb->port_mode_off);
		if (ret) {
			dev_dbg(mac_cb->dev,
				"mac%d port-mode-offset not found, use default value.\n",
				mac_cb->mac_id);
		}

		ret = of_parse_phandle_with_fixed_args(
			to_of_node(mac_cb->fw_port), "cpld-syscon", 1, 0,
			&cpld_args);
		if (ret) {
			dev_dbg(mac_cb->dev, "mac%d no cpld-syscon found.\n",
				mac_cb->mac_id);
			mac_cb->cpld_ctrl = NULL;
		} else {
			syscon = syscon_node_to_regmap(cpld_args.np);
			if (IS_ERR_OR_NULL(syscon)) {
				dev_dbg(mac_cb->dev, "no cpld-syscon found!\n");
				mac_cb->cpld_ctrl = NULL;
			} else {
				mac_cb->cpld_ctrl = syscon;
				mac_cb->cpld_ctrl_reg = cpld_args.args[0];
			}
		}
	} else if (is_acpi_node(mac_cb->fw_port)) {
		ret = hns_mac_register_phy(mac_cb);
		/*
		 * Mac can work well if there is phy or not.If the port don't
		 * connect with phy, the return value will be ignored. Only
		 * when there is phy but can't find mdio bus, the return value
		 * will be handled.
		 */
		if (ret == -EPROBE_DEFER)
			return ret;
	} else {
		dev_err(mac_cb->dev, "mac%d cannot find phy node\n",
			mac_cb->mac_id);
	}

	if (!fwnode_property_read_string(mac_cb->fw_port, "media-type",
					 &media_type)) {
		for (i = 0; i < ARRAY_SIZE(media_type_defs); i++) {
			if (!strncmp(media_type_defs[i].name, media_type,
				     MAC_MEDIA_TYPE_MAX_LEN)) {
				mac_cb->media_type = media_type_defs[i].value;
				break;
			}
		}
	}

	if (fwnode_property_read_u8_array(mac_cb->fw_port, "mc-mac-mask",
					  mac_cb->mc_mask, ETH_ALEN)) {
		dev_warn(mac_cb->dev,
			 "no mc-mac-mask property, set to default value.\n");
		eth_broadcast_addr(mac_cb->mc_mask);
	}

	return 0;
}