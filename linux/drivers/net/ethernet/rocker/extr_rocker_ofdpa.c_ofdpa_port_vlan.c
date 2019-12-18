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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ofdpa_port {int /*<<< orphan*/  vlan_bitmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  pport; } ;
typedef  enum rocker_of_dpa_table_id { ____Placeholder_rocker_of_dpa_table_id } rocker_of_dpa_table_id ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int OFDPA_OP_FLAG_REMOVE ; 
 int ROCKER_OF_DPA_TABLE_ID_TERMINATION_MAC ; 
 int /*<<< orphan*/  change_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int ofdpa_flow_tbl_vlan (struct ofdpa_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int ofdpa_port_ctrl_vlan_add (struct ofdpa_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_port_vid_to_vlan (struct ofdpa_port*,int,int*) ; 
 int ofdpa_port_vlan_flood_group (struct ofdpa_port*,int,int /*<<< orphan*/ ) ; 
 int ofdpa_port_vlan_l2_groups (struct ofdpa_port*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_vlan(struct ofdpa_port *ofdpa_port, int flags,
			   u16 vid)
{
	enum rocker_of_dpa_table_id goto_tbl =
			ROCKER_OF_DPA_TABLE_ID_TERMINATION_MAC;
	u32 in_pport = ofdpa_port->pport;
	__be16 vlan_id = htons(vid);
	__be16 vlan_id_mask = htons(0xffff);
	__be16 internal_vlan_id;
	bool untagged;
	bool adding = !(flags & OFDPA_OP_FLAG_REMOVE);
	int err;

	internal_vlan_id = ofdpa_port_vid_to_vlan(ofdpa_port, vid, &untagged);

	if (adding &&
	    test_bit(ntohs(internal_vlan_id), ofdpa_port->vlan_bitmap))
		return 0; /* already added */
	else if (!adding &&
		 !test_bit(ntohs(internal_vlan_id), ofdpa_port->vlan_bitmap))
		return 0; /* already removed */

	change_bit(ntohs(internal_vlan_id), ofdpa_port->vlan_bitmap);

	if (adding) {
		err = ofdpa_port_ctrl_vlan_add(ofdpa_port, flags,
					       internal_vlan_id);
		if (err) {
			netdev_err(ofdpa_port->dev, "Error (%d) port ctrl vlan add\n", err);
			goto err_vlan_add;
		}
	}

	err = ofdpa_port_vlan_l2_groups(ofdpa_port, flags,
					internal_vlan_id, untagged);
	if (err) {
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 groups\n", err);
		goto err_vlan_l2_groups;
	}

	err = ofdpa_port_vlan_flood_group(ofdpa_port, flags,
					  internal_vlan_id);
	if (err) {
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 flood group\n", err);
		goto err_flood_group;
	}

	err = ofdpa_flow_tbl_vlan(ofdpa_port, flags,
				  in_pport, vlan_id, vlan_id_mask,
				  goto_tbl, untagged, internal_vlan_id);
	if (err)
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN table\n", err);

	return 0;

err_vlan_add:
err_vlan_l2_groups:
err_flood_group:
	change_bit(ntohs(internal_vlan_id), ofdpa_port->vlan_bitmap);
	return err;
}