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
struct sja1105_table {int entry_count; struct sja1105_mac_config_entry* entries; TYPE_2__* ops; } ;
struct TYPE_3__ {struct sja1105_table* tables; } ;
struct sja1105_private {int /*<<< orphan*/  ds; TYPE_1__ static_config; } ;
struct sja1105_mac_config_entry {int maxage; int vlanid; int ing_mirr; int egr_mirr; int drpnona664; int drpdtag; int drpuntag; int retag; int dyn_learn; int egress; int ingress; int /*<<< orphan*/  vlanprio; int /*<<< orphan*/  tp_delout; int /*<<< orphan*/  tp_delin; int /*<<< orphan*/  speed; int /*<<< orphan*/  ifg; int /*<<< orphan*/  enabled; int /*<<< orphan*/  base; int /*<<< orphan*/  top; } ;
struct TYPE_4__ {int /*<<< orphan*/  unpacked_entry_size; } ;

/* Variables and functions */
 size_t BLK_IDX_MAC_CONFIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SJA1105_NUM_PORTS ; 
 int /*<<< orphan*/  SJA1105_SPEED_AUTO ; 
 int dsa_upstream_port (int /*<<< orphan*/ ,int) ; 
 struct sja1105_mac_config_entry* kcalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sja1105_mac_config_entry*) ; 

__attribute__((used)) static int sja1105_init_mac_settings(struct sja1105_private *priv)
{
	struct sja1105_mac_config_entry default_mac = {
		/* Enable all 8 priority queues on egress.
		 * Every queue i holds top[i] - base[i] frames.
		 * Sum of top[i] - base[i] is 511 (max hardware limit).
		 */
		.top  = {0x3F, 0x7F, 0xBF, 0xFF, 0x13F, 0x17F, 0x1BF, 0x1FF},
		.base = {0x0, 0x40, 0x80, 0xC0, 0x100, 0x140, 0x180, 0x1C0},
		.enabled = {true, true, true, true, true, true, true, true},
		/* Keep standard IFG of 12 bytes on egress. */
		.ifg = 0,
		/* Always put the MAC speed in automatic mode, where it can be
		 * adjusted at runtime by PHYLINK.
		 */
		.speed = SJA1105_SPEED_AUTO,
		/* No static correction for 1-step 1588 events */
		.tp_delin = 0,
		.tp_delout = 0,
		/* Disable aging for critical TTEthernet traffic */
		.maxage = 0xFF,
		/* Internal VLAN (pvid) to apply to untagged ingress */
		.vlanprio = 0,
		.vlanid = 1,
		.ing_mirr = false,
		.egr_mirr = false,
		/* Don't drop traffic with other EtherType than ETH_P_IP */
		.drpnona664 = false,
		/* Don't drop double-tagged traffic */
		.drpdtag = false,
		/* Don't drop untagged traffic */
		.drpuntag = false,
		/* Don't retag 802.1p (VID 0) traffic with the pvid */
		.retag = false,
		/* Disable learning and I/O on user ports by default -
		 * STP will enable it.
		 */
		.dyn_learn = false,
		.egress = false,
		.ingress = false,
	};
	struct sja1105_mac_config_entry *mac;
	struct sja1105_table *table;
	int i;

	table = &priv->static_config.tables[BLK_IDX_MAC_CONFIG];

	/* Discard previous MAC Configuration Table */
	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	table->entries = kcalloc(SJA1105_NUM_PORTS,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	if (!table->entries)
		return -ENOMEM;

	table->entry_count = SJA1105_NUM_PORTS;

	mac = table->entries;

	for (i = 0; i < SJA1105_NUM_PORTS; i++) {
		mac[i] = default_mac;
		if (i == dsa_upstream_port(priv->ds, i)) {
			/* STP doesn't get called for CPU port, so we need to
			 * set the I/O parameters statically.
			 */
			mac[i].dyn_learn = true;
			mac[i].ingress = true;
			mac[i].egress = true;
		}
	}

	return 0;
}