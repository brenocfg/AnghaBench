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
struct sja1105_private {int dummy; } ;
struct sja1105_dt_port {int dummy; } ;
struct dsa_switch {int vlan_filtering_is_global; int /*<<< orphan*/  num_tx_queues; int /*<<< orphan*/  dev; struct sja1105_private* priv; } ;

/* Variables and functions */
 int SJA1105_NUM_PORTS ; 
 int /*<<< orphan*/  SJA1105_NUM_TC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int sja1105_clocking_setup (struct sja1105_private*) ; 
 int sja1105_parse_dt (struct sja1105_private*,struct sja1105_dt_port*) ; 
 int sja1105_parse_rgmii_delays (struct sja1105_private*,struct sja1105_dt_port*) ; 
 int sja1105_ptp_clock_register (struct sja1105_private*) ; 
 int sja1105_setup_8021q_tagging (struct dsa_switch*,int) ; 
 int sja1105_static_config_load (struct sja1105_private*,struct sja1105_dt_port*) ; 

__attribute__((used)) static int sja1105_setup(struct dsa_switch *ds)
{
	struct sja1105_dt_port ports[SJA1105_NUM_PORTS];
	struct sja1105_private *priv = ds->priv;
	int rc;

	rc = sja1105_parse_dt(priv, ports);
	if (rc < 0) {
		dev_err(ds->dev, "Failed to parse DT: %d\n", rc);
		return rc;
	}

	/* Error out early if internal delays are required through DT
	 * and we can't apply them.
	 */
	rc = sja1105_parse_rgmii_delays(priv, ports);
	if (rc < 0) {
		dev_err(ds->dev, "RGMII delay not supported\n");
		return rc;
	}

	rc = sja1105_ptp_clock_register(priv);
	if (rc < 0) {
		dev_err(ds->dev, "Failed to register PTP clock: %d\n", rc);
		return rc;
	}
	/* Create and send configuration down to device */
	rc = sja1105_static_config_load(priv, ports);
	if (rc < 0) {
		dev_err(ds->dev, "Failed to load static config: %d\n", rc);
		return rc;
	}
	/* Configure the CGU (PHY link modes and speeds) */
	rc = sja1105_clocking_setup(priv);
	if (rc < 0) {
		dev_err(ds->dev, "Failed to configure MII clocking: %d\n", rc);
		return rc;
	}
	/* On SJA1105, VLAN filtering per se is always enabled in hardware.
	 * The only thing we can do to disable it is lie about what the 802.1Q
	 * EtherType is.
	 * So it will still try to apply VLAN filtering, but all ingress
	 * traffic (except frames received with EtherType of ETH_P_SJA1105)
	 * will be internally tagged with a distorted VLAN header where the
	 * TPID is ETH_P_SJA1105, and the VLAN ID is the port pvid.
	 */
	ds->vlan_filtering_is_global = true;

	/* Advertise the 8 egress queues */
	ds->num_tx_queues = SJA1105_NUM_TC;

	/* The DSA/switchdev model brings up switch ports in standalone mode by
	 * default, and that means vlan_filtering is 0 since they're not under
	 * a bridge, so it's safe to set up switch tagging at this time.
	 */
	return sja1105_setup_8021q_tagging(ds, true);
}