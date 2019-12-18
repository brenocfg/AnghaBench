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
typedef  scalar_t__ u16 ;
struct sja1105_vlan_lookup_entry {scalar_t__ vlanid; } ;
struct TYPE_4__ {TYPE_1__* tables; } ;
struct sja1105_private {TYPE_2__ static_config; } ;
struct TYPE_3__ {int entry_count; struct sja1105_vlan_lookup_entry* entries; } ;

/* Variables and functions */
 size_t BLK_IDX_VLAN_LOOKUP ; 

__attribute__((used)) static int sja1105_is_vlan_configured(struct sja1105_private *priv, u16 vid)
{
	struct sja1105_vlan_lookup_entry *vlan;
	int count, i;

	vlan = priv->static_config.tables[BLK_IDX_VLAN_LOOKUP].entries;
	count = priv->static_config.tables[BLK_IDX_VLAN_LOOKUP].entry_count;

	for (i = 0; i < count; i++)
		if (vlan[i].vlanid == vid)
			return i;

	/* Return an invalid entry index if not found */
	return -1;
}