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
typedef  size_t u16 ;
struct ocelot {int num_phys_ports; scalar_t__* vlan_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_PORT_VLAN_CFG ; 
 int ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA ; 
 int ANA_PORT_VLAN_CFG_VLAN_POP_CNT (int) ; 
 int ANA_PORT_VLAN_CFG_VLAN_VID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ANA_TABLES_VLANACCESS ; 
 scalar_t__ ANA_TABLES_VLANACCESS_CMD_INIT ; 
 int /*<<< orphan*/  ANA_VLANMASK ; 
 scalar_t__ GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REW_PORT_VLAN_CFG ; 
 int /*<<< orphan*/  REW_TAG_CFG ; 
 size_t VLAN_N_VID ; 
 int /*<<< orphan*/  ocelot_vlant_set_mask (struct ocelot*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ocelot_vlant_wait_for_completion (struct ocelot*) ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write_gix (struct ocelot*,int,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void ocelot_vlan_init(struct ocelot *ocelot)
{
	u16 port, vid;

	/* Clear VLAN table, by default all ports are members of all VLANs */
	ocelot_write(ocelot, ANA_TABLES_VLANACCESS_CMD_INIT,
		     ANA_TABLES_VLANACCESS);
	ocelot_vlant_wait_for_completion(ocelot);

	/* Configure the port VLAN memberships */
	for (vid = 1; vid < VLAN_N_VID; vid++) {
		ocelot->vlan_mask[vid] = 0;
		ocelot_vlant_set_mask(ocelot, vid, ocelot->vlan_mask[vid]);
	}

	/* Because VLAN filtering is enabled, we need VID 0 to get untagged
	 * traffic.  It is added automatically if 8021q module is loaded, but
	 * we can't rely on it since module may be not loaded.
	 */
	ocelot->vlan_mask[0] = GENMASK(ocelot->num_phys_ports - 1, 0);
	ocelot_vlant_set_mask(ocelot, 0, ocelot->vlan_mask[0]);

	/* Configure the CPU port to be VLAN aware */
	ocelot_write_gix(ocelot, ANA_PORT_VLAN_CFG_VLAN_VID(0) |
				 ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA |
				 ANA_PORT_VLAN_CFG_VLAN_POP_CNT(1),
			 ANA_PORT_VLAN_CFG, ocelot->num_phys_ports);

	/* Set vlan ingress filter mask to all ports but the CPU port by
	 * default.
	 */
	ocelot_write(ocelot, GENMASK(9, 0), ANA_VLANMASK);

	for (port = 0; port < ocelot->num_phys_ports; port++) {
		ocelot_write_gix(ocelot, 0, REW_PORT_VLAN_CFG, port);
		ocelot_write_gix(ocelot, 0, REW_TAG_CFG, port);
	}
}