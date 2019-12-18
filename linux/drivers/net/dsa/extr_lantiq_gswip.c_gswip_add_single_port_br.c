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
struct gswip_priv {int /*<<< orphan*/  dev; TYPE_1__* hw_info; } ;
struct gswip_pce_table_entry {int index; int* val; int valid; int /*<<< orphan*/  table; scalar_t__* key; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {unsigned int cpu_port; unsigned int max_ports; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EIO ; 
 int /*<<< orphan*/  GSWIP_TABLE_ACTIVE_VLAN ; 
 int /*<<< orphan*/  GSWIP_TABLE_VLAN_MAPPING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gswip_pce_table_entry_write (struct gswip_priv*,struct gswip_pce_table_entry*) ; 

__attribute__((used)) static int gswip_add_single_port_br(struct gswip_priv *priv, int port, bool add)
{
	struct gswip_pce_table_entry vlan_active = {0,};
	struct gswip_pce_table_entry vlan_mapping = {0,};
	unsigned int cpu_port = priv->hw_info->cpu_port;
	unsigned int max_ports = priv->hw_info->max_ports;
	int err;

	if (port >= max_ports) {
		dev_err(priv->dev, "single port for %i supported\n", port);
		return -EIO;
	}

	vlan_active.index = port + 1;
	vlan_active.table = GSWIP_TABLE_ACTIVE_VLAN;
	vlan_active.key[0] = 0; /* vid */
	vlan_active.val[0] = port + 1 /* fid */;
	vlan_active.valid = add;
	err = gswip_pce_table_entry_write(priv, &vlan_active);
	if (err) {
		dev_err(priv->dev, "failed to write active VLAN: %d\n", err);
		return err;
	}

	if (!add)
		return 0;

	vlan_mapping.index = port + 1;
	vlan_mapping.table = GSWIP_TABLE_VLAN_MAPPING;
	vlan_mapping.val[0] = 0 /* vid */;
	vlan_mapping.val[1] = BIT(port) | BIT(cpu_port);
	vlan_mapping.val[2] = 0;
	err = gswip_pce_table_entry_write(priv, &vlan_mapping);
	if (err) {
		dev_err(priv->dev, "failed to write VLAN mapping: %d\n", err);
		return err;
	}

	return 0;
}