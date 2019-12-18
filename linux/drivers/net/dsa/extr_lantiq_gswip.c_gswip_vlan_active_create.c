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
typedef  void* u16 ;
struct net_device {int dummy; } ;
struct gswip_priv {TYPE_2__* vlans; int /*<<< orphan*/  dev; TYPE_1__* hw_info; } ;
struct gswip_pce_table_entry {int index; int* val; int valid; void** key; int /*<<< orphan*/  table; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int fid; void* vid; struct net_device* bridge; } ;
struct TYPE_3__ {unsigned int max_ports; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GSWIP_TABLE_ACTIVE_VLAN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gswip_pce_table_entry_write (struct gswip_priv*,struct gswip_pce_table_entry*) ; 

__attribute__((used)) static int gswip_vlan_active_create(struct gswip_priv *priv,
				    struct net_device *bridge,
				    int fid, u16 vid)
{
	struct gswip_pce_table_entry vlan_active = {0,};
	unsigned int max_ports = priv->hw_info->max_ports;
	int idx = -1;
	int err;
	int i;

	/* Look for a free slot */
	for (i = max_ports; i < ARRAY_SIZE(priv->vlans); i++) {
		if (!priv->vlans[i].bridge) {
			idx = i;
			break;
		}
	}

	if (idx == -1)
		return -ENOSPC;

	if (fid == -1)
		fid = idx;

	vlan_active.index = idx;
	vlan_active.table = GSWIP_TABLE_ACTIVE_VLAN;
	vlan_active.key[0] = vid;
	vlan_active.val[0] = fid;
	vlan_active.valid = true;

	err = gswip_pce_table_entry_write(priv, &vlan_active);
	if (err) {
		dev_err(priv->dev, "failed to write active VLAN: %d\n",	err);
		return err;
	}

	priv->vlans[idx].bridge = bridge;
	priv->vlans[idx].vid = vid;
	priv->vlans[idx].fid = fid;

	return idx;
}