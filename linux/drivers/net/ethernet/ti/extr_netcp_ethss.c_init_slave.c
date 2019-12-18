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
typedef  int u32 ;
struct gbe_slave {scalar_t__ slave_num; scalar_t__ link_interface; int open; int port_regs; int emac_regs; int /*<<< orphan*/  link_state; int /*<<< orphan*/  mac_control; int /*<<< orphan*/  port_num; int /*<<< orphan*/  phy_node; struct device_node* node; } ;
struct gbe_priv {int switch_regs; int /*<<< orphan*/  ss_version; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int GBE13_EMAC_OFFSET ; 
 int GBE13_SLAVE_PORT2_OFFSET ; 
 int GBE13_SLAVE_PORT_OFFSET ; 
 int GBENU_EMAC_OFFSET ; 
 int /*<<< orphan*/  GBENU_SET_REG_OFS (struct gbe_slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GBENU_SLAVE_PORT_OFFSET ; 
 int /*<<< orphan*/  GBE_DEF_10G_MAC_CONTROL ; 
 int /*<<< orphan*/  GBE_DEF_1G_MAC_CONTROL ; 
 int /*<<< orphan*/  GBE_SET_REG_OFS (struct gbe_slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SS_ID_MU (struct gbe_priv*) ; 
 scalar_t__ IS_SS_ID_VER_14 (struct gbe_priv*) ; 
 scalar_t__ IS_SS_ID_XGBE (struct gbe_priv*) ; 
 int /*<<< orphan*/  NETCP_LINK_STATE_INVALID ; 
 scalar_t__ RGMII_LINK_MAC_PHY ; 
 scalar_t__ SGMII_LINK_MAC_PHY ; 
 int XGBE10_EMAC_OFFSET ; 
 int XGBE10_SLAVE_PORT_OFFSET ; 
 int /*<<< orphan*/  XGBE_SET_REG_OFS (struct gbe_slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XGMII_LINK_MAC_PHY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  emac_regs ; 
 int /*<<< orphan*/  gbe_get_slave_port (struct gbe_priv*,scalar_t__) ; 
 int /*<<< orphan*/  init_slave_ts_ctl (struct gbe_slave*) ; 
 int /*<<< orphan*/  mac_control ; 
 int /*<<< orphan*/  of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  port_regs ; 
 int /*<<< orphan*/  port_vlan ; 
 int /*<<< orphan*/  rx_maxlen ; 
 int /*<<< orphan*/  rx_pri_map ; 
 int /*<<< orphan*/  sa_hi ; 
 int /*<<< orphan*/  sa_lo ; 
 int /*<<< orphan*/  soft_reset ; 
 int /*<<< orphan*/  ts_ctl ; 
 int /*<<< orphan*/  ts_ctl2 ; 
 int /*<<< orphan*/  ts_ctl_ltype2 ; 
 int /*<<< orphan*/  ts_seq_ltype ; 
 int /*<<< orphan*/  ts_vlan ; 
 int /*<<< orphan*/  tx_pri_map ; 

__attribute__((used)) static int init_slave(struct gbe_priv *gbe_dev, struct gbe_slave *slave,
		      struct device_node *node)
{
	int port_reg_num;
	u32 port_reg_ofs, emac_reg_ofs;
	u32 port_reg_blk_sz, emac_reg_blk_sz;

	if (of_property_read_u32(node, "slave-port", &slave->slave_num)) {
		dev_err(gbe_dev->dev, "missing slave-port parameter\n");
		return -EINVAL;
	}

	if (of_property_read_u32(node, "link-interface",
				 &slave->link_interface)) {
		dev_warn(gbe_dev->dev,
			 "missing link-interface value defaulting to 1G mac-phy link\n");
		slave->link_interface = SGMII_LINK_MAC_PHY;
	}

	slave->node = node;
	slave->open = false;
	if ((slave->link_interface == SGMII_LINK_MAC_PHY) ||
	    (slave->link_interface == RGMII_LINK_MAC_PHY) ||
	    (slave->link_interface == XGMII_LINK_MAC_PHY))
		slave->phy_node = of_parse_phandle(node, "phy-handle", 0);
	slave->port_num = gbe_get_slave_port(gbe_dev, slave->slave_num);

	if (slave->link_interface >= XGMII_LINK_MAC_PHY)
		slave->mac_control = GBE_DEF_10G_MAC_CONTROL;
	else
		slave->mac_control = GBE_DEF_1G_MAC_CONTROL;

	/* Emac regs memmap are contiguous but port regs are not */
	port_reg_num = slave->slave_num;
	if (IS_SS_ID_VER_14(gbe_dev)) {
		if (slave->slave_num > 1) {
			port_reg_ofs = GBE13_SLAVE_PORT2_OFFSET;
			port_reg_num -= 2;
		} else {
			port_reg_ofs = GBE13_SLAVE_PORT_OFFSET;
		}
		emac_reg_ofs = GBE13_EMAC_OFFSET;
		port_reg_blk_sz = 0x30;
		emac_reg_blk_sz = 0x40;
	} else if (IS_SS_ID_MU(gbe_dev)) {
		port_reg_ofs = GBENU_SLAVE_PORT_OFFSET;
		emac_reg_ofs = GBENU_EMAC_OFFSET;
		port_reg_blk_sz = 0x1000;
		emac_reg_blk_sz = 0x1000;
	} else if (IS_SS_ID_XGBE(gbe_dev)) {
		port_reg_ofs = XGBE10_SLAVE_PORT_OFFSET;
		emac_reg_ofs = XGBE10_EMAC_OFFSET;
		port_reg_blk_sz = 0x30;
		emac_reg_blk_sz = 0x40;
	} else {
		dev_err(gbe_dev->dev, "unknown ethss(0x%x)\n",
			gbe_dev->ss_version);
		return -EINVAL;
	}

	slave->port_regs = gbe_dev->switch_regs + port_reg_ofs +
				(port_reg_blk_sz * port_reg_num);
	slave->emac_regs = gbe_dev->switch_regs + emac_reg_ofs +
				(emac_reg_blk_sz * slave->slave_num);

	if (IS_SS_ID_VER_14(gbe_dev)) {
		/* Initialize  slave port register offsets */
		GBE_SET_REG_OFS(slave, port_regs, port_vlan);
		GBE_SET_REG_OFS(slave, port_regs, tx_pri_map);
		GBE_SET_REG_OFS(slave, port_regs, sa_lo);
		GBE_SET_REG_OFS(slave, port_regs, sa_hi);
		GBE_SET_REG_OFS(slave, port_regs, ts_ctl);
		GBE_SET_REG_OFS(slave, port_regs, ts_seq_ltype);
		GBE_SET_REG_OFS(slave, port_regs, ts_vlan);
		GBE_SET_REG_OFS(slave, port_regs, ts_ctl_ltype2);
		GBE_SET_REG_OFS(slave, port_regs, ts_ctl2);

		/* Initialize EMAC register offsets */
		GBE_SET_REG_OFS(slave, emac_regs, mac_control);
		GBE_SET_REG_OFS(slave, emac_regs, soft_reset);
		GBE_SET_REG_OFS(slave, emac_regs, rx_maxlen);

	} else if (IS_SS_ID_MU(gbe_dev)) {
		/* Initialize  slave port register offsets */
		GBENU_SET_REG_OFS(slave, port_regs, port_vlan);
		GBENU_SET_REG_OFS(slave, port_regs, tx_pri_map);
		GBENU_SET_REG_OFS(slave, port_regs, rx_pri_map);
		GBENU_SET_REG_OFS(slave, port_regs, sa_lo);
		GBENU_SET_REG_OFS(slave, port_regs, sa_hi);
		GBENU_SET_REG_OFS(slave, port_regs, ts_ctl);
		GBENU_SET_REG_OFS(slave, port_regs, ts_seq_ltype);
		GBENU_SET_REG_OFS(slave, port_regs, ts_vlan);
		GBENU_SET_REG_OFS(slave, port_regs, ts_ctl_ltype2);
		GBENU_SET_REG_OFS(slave, port_regs, ts_ctl2);
		GBENU_SET_REG_OFS(slave, port_regs, rx_maxlen);

		/* Initialize EMAC register offsets */
		GBENU_SET_REG_OFS(slave, emac_regs, mac_control);
		GBENU_SET_REG_OFS(slave, emac_regs, soft_reset);

	} else if (IS_SS_ID_XGBE(gbe_dev)) {
		/* Initialize  slave port register offsets */
		XGBE_SET_REG_OFS(slave, port_regs, port_vlan);
		XGBE_SET_REG_OFS(slave, port_regs, tx_pri_map);
		XGBE_SET_REG_OFS(slave, port_regs, sa_lo);
		XGBE_SET_REG_OFS(slave, port_regs, sa_hi);
		XGBE_SET_REG_OFS(slave, port_regs, ts_ctl);
		XGBE_SET_REG_OFS(slave, port_regs, ts_seq_ltype);
		XGBE_SET_REG_OFS(slave, port_regs, ts_vlan);
		XGBE_SET_REG_OFS(slave, port_regs, ts_ctl_ltype2);
		XGBE_SET_REG_OFS(slave, port_regs, ts_ctl2);

		/* Initialize EMAC register offsets */
		XGBE_SET_REG_OFS(slave, emac_regs, mac_control);
		XGBE_SET_REG_OFS(slave, emac_regs, soft_reset);
		XGBE_SET_REG_OFS(slave, emac_regs, rx_maxlen);
	}

	atomic_set(&slave->link_state, NETCP_LINK_STATE_INVALID);

	init_slave_ts_ctl(slave);
	return 0;
}