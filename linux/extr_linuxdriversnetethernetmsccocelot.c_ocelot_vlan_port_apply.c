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
struct ocelot_port {int /*<<< orphan*/  chip_port; scalar_t__ vid; scalar_t__ vlan_aware; int /*<<< orphan*/  pvid; } ;
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_PORT_DROP_CFG ; 
 int ANA_PORT_DROP_CFG_DROP_MC_SMAC_ENA ; 
 int ANA_PORT_DROP_CFG_DROP_PRIO_C_TAGGED_ENA ; 
 int ANA_PORT_DROP_CFG_DROP_PRIO_S_TAGGED_ENA ; 
 int ANA_PORT_DROP_CFG_DROP_UNTAGGED_ENA ; 
 int /*<<< orphan*/  ANA_PORT_VLAN_CFG ; 
 int ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA ; 
 int ANA_PORT_VLAN_CFG_VLAN_POP_CNT (int) ; 
 int ANA_PORT_VLAN_CFG_VLAN_POP_CNT_M ; 
 int ANA_PORT_VLAN_CFG_VLAN_VID (int /*<<< orphan*/ ) ; 
 int ANA_PORT_VLAN_CFG_VLAN_VID_M ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  REW_PORT_VLAN_CFG ; 
 int REW_PORT_VLAN_CFG_PORT_TPID (int /*<<< orphan*/ ) ; 
 int REW_PORT_VLAN_CFG_PORT_TPID_M ; 
 int REW_PORT_VLAN_CFG_PORT_VID (scalar_t__) ; 
 int REW_PORT_VLAN_CFG_PORT_VID_M ; 
 int /*<<< orphan*/  REW_TAG_CFG ; 
 int REW_TAG_CFG_TAG_CFG (int) ; 
 int REW_TAG_CFG_TAG_CFG_M ; 
 int REW_TAG_CFG_TAG_TPID_CFG (int /*<<< orphan*/ ) ; 
 int REW_TAG_CFG_TAG_TPID_CFG_M ; 
 int /*<<< orphan*/  ocelot_rmw_gix (struct ocelot*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write_gix (struct ocelot*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocelot_vlan_port_apply(struct ocelot *ocelot,
				   struct ocelot_port *port)
{
	u32 val;

	/* Ingress clasification (ANA_PORT_VLAN_CFG) */
	/* Default vlan to clasify for untagged frames (may be zero) */
	val = ANA_PORT_VLAN_CFG_VLAN_VID(port->pvid);
	if (port->vlan_aware)
		val |= ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA |
		       ANA_PORT_VLAN_CFG_VLAN_POP_CNT(1);

	ocelot_rmw_gix(ocelot, val,
		       ANA_PORT_VLAN_CFG_VLAN_VID_M |
		       ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA |
		       ANA_PORT_VLAN_CFG_VLAN_POP_CNT_M,
		       ANA_PORT_VLAN_CFG, port->chip_port);

	/* Drop frames with multicast source address */
	val = ANA_PORT_DROP_CFG_DROP_MC_SMAC_ENA;
	if (port->vlan_aware && !port->vid)
		/* If port is vlan-aware and tagged, drop untagged and priority
		 * tagged frames.
		 */
		val |= ANA_PORT_DROP_CFG_DROP_UNTAGGED_ENA |
		       ANA_PORT_DROP_CFG_DROP_PRIO_S_TAGGED_ENA |
		       ANA_PORT_DROP_CFG_DROP_PRIO_C_TAGGED_ENA;
	ocelot_write_gix(ocelot, val, ANA_PORT_DROP_CFG, port->chip_port);

	/* Egress configuration (REW_TAG_CFG): VLAN tag type to 8021Q. */
	val = REW_TAG_CFG_TAG_TPID_CFG(0);

	if (port->vlan_aware) {
		if (port->vid)
			/* Tag all frames except when VID == DEFAULT_VLAN */
			val |= REW_TAG_CFG_TAG_CFG(1);
		else
			/* Tag all frames */
			val |= REW_TAG_CFG_TAG_CFG(3);
	}
	ocelot_rmw_gix(ocelot, val,
		       REW_TAG_CFG_TAG_TPID_CFG_M |
		       REW_TAG_CFG_TAG_CFG_M,
		       REW_TAG_CFG, port->chip_port);

	/* Set default VLAN and tag type to 8021Q. */
	val = REW_PORT_VLAN_CFG_PORT_TPID(ETH_P_8021Q) |
	      REW_PORT_VLAN_CFG_PORT_VID(port->vid);
	ocelot_rmw_gix(ocelot, val,
		       REW_PORT_VLAN_CFG_PORT_TPID_M |
		       REW_PORT_VLAN_CFG_PORT_VID_M,
		       REW_PORT_VLAN_CFG, port->chip_port);
}