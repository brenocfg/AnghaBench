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
struct vlan_table {int dummy; } ;
struct ksz_device {int /*<<< orphan*/  host_mask; int /*<<< orphan*/ * regmap; int /*<<< orphan*/  vlan_cache; int /*<<< orphan*/  num_vlans; int /*<<< orphan*/  dev; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct ksz_device* priv; } ;
struct alu_struct {int is_static; int is_override; int /*<<< orphan*/  port_forward; int /*<<< orphan*/  mac; } ;
typedef  int /*<<< orphan*/  alu ;

/* Variables and functions */
 int BROADCAST_STORM_PROT_RATE ; 
 int BROADCAST_STORM_RATE ; 
 int BROADCAST_STORM_VALUE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MULTICAST_STORM_DISABLE ; 
 int NO_EXC_COLLISION_DROP ; 
 int /*<<< orphan*/  REG_SW_CTRL_1 ; 
 int /*<<< orphan*/  REG_SW_CTRL_2 ; 
 int SW_AGGR_BACKOFF ; 
 int /*<<< orphan*/  SW_FLOW_CTRL ; 
 int /*<<< orphan*/  SW_LINK_AUTO_AGING ; 
 int /*<<< orphan*/  SW_MIRROR_RX_TX ; 
 int /*<<< orphan*/  SW_REPLACE_VID ; 
 int /*<<< orphan*/  S_LINK_AGING_CTRL ; 
 int /*<<< orphan*/  S_MIRROR_CTRL ; 
 int /*<<< orphan*/  S_REPLACE_VID_CTRL ; 
 int UNICAST_VLAN_BOUNDARY ; 
 int VLAN_TABLE_ENTRIES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_stp_addr ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksz8795_config_cpu_port (struct dsa_switch*) ; 
 int /*<<< orphan*/  ksz8795_r_vlan_entries (struct ksz_device*,int) ; 
 int ksz8795_reset_switch (struct ksz_device*) ; 
 int /*<<< orphan*/  ksz8795_w_sta_mac_table (struct ksz_device*,int /*<<< orphan*/ ,struct alu_struct*) ; 
 int /*<<< orphan*/  ksz_cfg (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_init_mib_timer (struct ksz_device*) ; 
 int /*<<< orphan*/  memset (struct alu_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ksz8795_setup(struct dsa_switch *ds)
{
	struct ksz_device *dev = ds->priv;
	struct alu_struct alu;
	int i, ret = 0;

	dev->vlan_cache = devm_kcalloc(dev->dev, sizeof(struct vlan_table),
				       dev->num_vlans, GFP_KERNEL);
	if (!dev->vlan_cache)
		return -ENOMEM;

	ret = ksz8795_reset_switch(dev);
	if (ret) {
		dev_err(ds->dev, "failed to reset switch\n");
		return ret;
	}

	ksz_cfg(dev, S_REPLACE_VID_CTRL, SW_FLOW_CTRL, true);

	/* Enable automatic fast aging when link changed detected. */
	ksz_cfg(dev, S_LINK_AGING_CTRL, SW_LINK_AUTO_AGING, true);

	/* Enable aggressive back off algorithm in half duplex mode. */
	regmap_update_bits(dev->regmap[0], REG_SW_CTRL_1,
			   SW_AGGR_BACKOFF, SW_AGGR_BACKOFF);

	/*
	 * Make sure unicast VLAN boundary is set as default and
	 * enable no excessive collision drop.
	 */
	regmap_update_bits(dev->regmap[0], REG_SW_CTRL_2,
			   UNICAST_VLAN_BOUNDARY | NO_EXC_COLLISION_DROP,
			   UNICAST_VLAN_BOUNDARY | NO_EXC_COLLISION_DROP);

	ksz8795_config_cpu_port(ds);

	ksz_cfg(dev, REG_SW_CTRL_2, MULTICAST_STORM_DISABLE, true);

	ksz_cfg(dev, S_REPLACE_VID_CTRL, SW_REPLACE_VID, false);

	ksz_cfg(dev, S_MIRROR_CTRL, SW_MIRROR_RX_TX, false);

	/* set broadcast storm protection 10% rate */
	regmap_update_bits(dev->regmap[1], S_REPLACE_VID_CTRL,
			   BROADCAST_STORM_RATE,
			   (BROADCAST_STORM_VALUE *
			   BROADCAST_STORM_PROT_RATE) / 100);

	for (i = 0; i < VLAN_TABLE_ENTRIES; i++)
		ksz8795_r_vlan_entries(dev, i);

	/* Setup STP address for STP operation. */
	memset(&alu, 0, sizeof(alu));
	ether_addr_copy(alu.mac, eth_stp_addr);
	alu.is_static = true;
	alu.is_override = true;
	alu.port_forward = dev->host_mask;

	ksz8795_w_sta_mac_table(dev, 0, &alu);

	ksz_init_mib_timer(dev);

	return 0;
}