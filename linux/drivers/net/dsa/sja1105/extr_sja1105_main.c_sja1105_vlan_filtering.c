#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct sja1105_table {struct sja1105_l2_lookup_params_entry* entries; } ;
struct TYPE_2__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_1__ static_config; } ;
struct sja1105_l2_lookup_params_entry {int incl_srcpt1; int incl_srcpt0; int shared_learn; void* tpid2; void* tpid; } ;
struct sja1105_general_params_entry {int incl_srcpt1; int incl_srcpt0; int shared_learn; void* tpid2; void* tpid; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct sja1105_private* priv; } ;

/* Variables and functions */
 size_t BLK_IDX_GENERAL_PARAMS ; 
 size_t BLK_IDX_L2_LOOKUP_PARAMS ; 
 void* ETH_P_8021AD ; 
 void* ETH_P_8021Q ; 
 void* ETH_P_SJA1105 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int sja1105_setup_8021q_tagging (struct dsa_switch*,int) ; 
 int sja1105_static_config_reload (struct sja1105_private*) ; 

__attribute__((used)) static int sja1105_vlan_filtering(struct dsa_switch *ds, int port, bool enabled)
{
	struct sja1105_l2_lookup_params_entry *l2_lookup_params;
	struct sja1105_general_params_entry *general_params;
	struct sja1105_private *priv = ds->priv;
	struct sja1105_table *table;
	u16 tpid, tpid2;
	int rc;

	if (enabled) {
		/* Enable VLAN filtering. */
		tpid  = ETH_P_8021AD;
		tpid2 = ETH_P_8021Q;
	} else {
		/* Disable VLAN filtering. */
		tpid  = ETH_P_SJA1105;
		tpid2 = ETH_P_SJA1105;
	}

	table = &priv->static_config.tables[BLK_IDX_GENERAL_PARAMS];
	general_params = table->entries;
	/* EtherType used to identify outer tagged (S-tag) VLAN traffic */
	general_params->tpid = tpid;
	/* EtherType used to identify inner tagged (C-tag) VLAN traffic */
	general_params->tpid2 = tpid2;
	/* When VLAN filtering is on, we need to at least be able to
	 * decode management traffic through the "backup plan".
	 */
	general_params->incl_srcpt1 = enabled;
	general_params->incl_srcpt0 = enabled;

	/* VLAN filtering => independent VLAN learning.
	 * No VLAN filtering => shared VLAN learning.
	 *
	 * In shared VLAN learning mode, untagged traffic still gets
	 * pvid-tagged, and the FDB table gets populated with entries
	 * containing the "real" (pvid or from VLAN tag) VLAN ID.
	 * However the switch performs a masked L2 lookup in the FDB,
	 * effectively only looking up a frame's DMAC (and not VID) for the
	 * forwarding decision.
	 *
	 * This is extremely convenient for us, because in modes with
	 * vlan_filtering=0, dsa_8021q actually installs unique pvid's into
	 * each front panel port. This is good for identification but breaks
	 * learning badly - the VID of the learnt FDB entry is unique, aka
	 * no frames coming from any other port are going to have it. So
	 * for forwarding purposes, this is as though learning was broken
	 * (all frames get flooded).
	 */
	table = &priv->static_config.tables[BLK_IDX_L2_LOOKUP_PARAMS];
	l2_lookup_params = table->entries;
	l2_lookup_params->shared_learn = !enabled;

	rc = sja1105_static_config_reload(priv);
	if (rc)
		dev_err(ds->dev, "Failed to change VLAN Ethertype\n");

	/* Switch port identification based on 802.1Q is only passable
	 * if we are not under a vlan_filtering bridge. So make sure
	 * the two configurations are mutually exclusive.
	 */
	return sja1105_setup_8021q_tagging(ds, !enabled);
}