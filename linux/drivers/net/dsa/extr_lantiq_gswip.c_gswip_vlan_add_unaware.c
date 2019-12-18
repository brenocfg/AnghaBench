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
struct net_device {int dummy; } ;
struct gswip_priv {int /*<<< orphan*/  dev; TYPE_2__* vlans; TYPE_1__* hw_info; } ;
struct gswip_pce_table_entry {int index; int /*<<< orphan*/ * val; void* table; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {struct net_device* bridge; } ;
struct TYPE_3__ {unsigned int max_ports; unsigned int cpu_port; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  GSWIP_PCE_DEFPVID (int) ; 
 void* GSWIP_TABLE_VLAN_MAPPING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gswip_pce_table_entry_read (struct gswip_priv*,struct gswip_pce_table_entry*) ; 
 int gswip_pce_table_entry_write (struct gswip_priv*,struct gswip_pce_table_entry*) ; 
 int /*<<< orphan*/  gswip_switch_w (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gswip_vlan_active_create (struct gswip_priv*,struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_vlan_active_remove (struct gswip_priv*,int) ; 

__attribute__((used)) static int gswip_vlan_add_unaware(struct gswip_priv *priv,
				  struct net_device *bridge, int port)
{
	struct gswip_pce_table_entry vlan_mapping = {0,};
	unsigned int max_ports = priv->hw_info->max_ports;
	unsigned int cpu_port = priv->hw_info->cpu_port;
	bool active_vlan_created = false;
	int idx = -1;
	int i;
	int err;

	/* Check if there is already a page for this bridge */
	for (i = max_ports; i < ARRAY_SIZE(priv->vlans); i++) {
		if (priv->vlans[i].bridge == bridge) {
			idx = i;
			break;
		}
	}

	/* If this bridge is not programmed yet, add a Active VLAN table
	 * entry in a free slot and prepare the VLAN mapping table entry.
	 */
	if (idx == -1) {
		idx = gswip_vlan_active_create(priv, bridge, -1, 0);
		if (idx < 0)
			return idx;
		active_vlan_created = true;

		vlan_mapping.index = idx;
		vlan_mapping.table = GSWIP_TABLE_VLAN_MAPPING;
		/* VLAN ID byte, maps to the VLAN ID of vlan active table */
		vlan_mapping.val[0] = 0;
	} else {
		/* Read the existing VLAN mapping entry from the switch */
		vlan_mapping.index = idx;
		vlan_mapping.table = GSWIP_TABLE_VLAN_MAPPING;
		err = gswip_pce_table_entry_read(priv, &vlan_mapping);
		if (err) {
			dev_err(priv->dev, "failed to read VLAN mapping: %d\n",
				err);
			return err;
		}
	}

	/* Update the VLAN mapping entry and write it to the switch */
	vlan_mapping.val[1] |= BIT(cpu_port);
	vlan_mapping.val[1] |= BIT(port);
	err = gswip_pce_table_entry_write(priv, &vlan_mapping);
	if (err) {
		dev_err(priv->dev, "failed to write VLAN mapping: %d\n", err);
		/* In case an Active VLAN was creaetd delete it again */
		if (active_vlan_created)
			gswip_vlan_active_remove(priv, idx);
		return err;
	}

	gswip_switch_w(priv, 0, GSWIP_PCE_DEFPVID(port));
	return 0;
}