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
struct sja1105_table {int entry_count; struct sja1105_l2_lookup_entry* entries; } ;
struct TYPE_2__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_1__ static_config; } ;
struct sja1105_l2_lookup_entry {scalar_t__ macaddr; scalar_t__ vlanid; int destports; } ;

/* Variables and functions */
 int BIT (int) ; 
 size_t BLK_IDX_L2_LOOKUP ; 

__attribute__((used)) static int
sja1105_find_static_fdb_entry(struct sja1105_private *priv, int port,
			      const struct sja1105_l2_lookup_entry *requested)
{
	struct sja1105_l2_lookup_entry *l2_lookup;
	struct sja1105_table *table;
	int i;

	table = &priv->static_config.tables[BLK_IDX_L2_LOOKUP];
	l2_lookup = table->entries;

	for (i = 0; i < table->entry_count; i++)
		if (l2_lookup[i].macaddr == requested->macaddr &&
		    l2_lookup[i].vlanid == requested->vlanid &&
		    l2_lookup[i].destports & BIT(port))
			return i;

	return -1;
}