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
struct mt7530_priv {int /*<<< orphan*/  ds; } ;
struct dsa_switch {int /*<<< orphan*/ * ports; struct mt7530_priv* priv; } ;

/* Variables and functions */
 int MT7530_CPU_PORT ; 
 int MT7530_NUM_PORTS ; 
 int /*<<< orphan*/  MT7530_PCR_P (int) ; 
 int /*<<< orphan*/  MT7530_PORT_MATRIX_MODE ; 
 int /*<<< orphan*/  MT7530_PVC_P (int) ; 
 int /*<<< orphan*/  MT7530_VLAN_TRANSPARENT ; 
 int /*<<< orphan*/  PCR_MATRIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCR_PORT_VLAN_MASK ; 
 int /*<<< orphan*/  PORT_SPEC_TAG ; 
 int /*<<< orphan*/  VLAN_ATTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLAN_ATTR_MASK ; 
 scalar_t__ dsa_is_user_port (struct dsa_switch*,int) ; 
 scalar_t__ dsa_port_is_vlan_filtering (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_user_ports (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_rmw (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_write (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7530_port_set_vlan_unaware(struct dsa_switch *ds, int port)
{
	struct mt7530_priv *priv = ds->priv;
	bool all_user_ports_removed = true;
	int i;

	/* When a port is removed from the bridge, the port would be set up
	 * back to the default as is at initial boot which is a VLAN-unaware
	 * port.
	 */
	mt7530_rmw(priv, MT7530_PCR_P(port), PCR_PORT_VLAN_MASK,
		   MT7530_PORT_MATRIX_MODE);
	mt7530_rmw(priv, MT7530_PVC_P(port), VLAN_ATTR_MASK,
		   VLAN_ATTR(MT7530_VLAN_TRANSPARENT));

	for (i = 0; i < MT7530_NUM_PORTS; i++) {
		if (dsa_is_user_port(ds, i) &&
		    dsa_port_is_vlan_filtering(&ds->ports[i])) {
			all_user_ports_removed = false;
			break;
		}
	}

	/* CPU port also does the same thing until all user ports belonging to
	 * the CPU port get out of VLAN filtering mode.
	 */
	if (all_user_ports_removed) {
		mt7530_write(priv, MT7530_PCR_P(MT7530_CPU_PORT),
			     PCR_MATRIX(dsa_user_ports(priv->ds)));
		mt7530_write(priv, MT7530_PVC_P(MT7530_CPU_PORT),
			     PORT_SPEC_TAG);
	}
}