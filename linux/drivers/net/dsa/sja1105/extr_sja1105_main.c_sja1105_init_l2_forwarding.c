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
struct sja1105_table {struct sja1105_l2_forwarding_entry* entries; scalar_t__ entry_count; TYPE_2__* ops; } ;
struct TYPE_3__ {struct sja1105_table* tables; } ;
struct sja1105_private {int /*<<< orphan*/  ds; TYPE_1__ static_config; } ;
struct sja1105_l2_forwarding_entry {int* vlan_pmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  unpacked_entry_size; } ;

/* Variables and functions */
 size_t BLK_IDX_L2_FORWARDING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SJA1105_MAX_L2_FORWARDING_COUNT ; 
 int SJA1105_NUM_PORTS ; 
 int SJA1105_NUM_TC ; 
 unsigned int dsa_upstream_port (int /*<<< orphan*/ ,int) ; 
 struct sja1105_l2_forwarding_entry* kcalloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sja1105_l2_forwarding_entry*) ; 
 int /*<<< orphan*/  sja1105_port_allow_traffic (struct sja1105_l2_forwarding_entry*,unsigned int,int,int) ; 

__attribute__((used)) static int sja1105_init_l2_forwarding(struct sja1105_private *priv)
{
	struct sja1105_l2_forwarding_entry *l2fwd;
	struct sja1105_table *table;
	int i, j;

	table = &priv->static_config.tables[BLK_IDX_L2_FORWARDING];

	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	table->entries = kcalloc(SJA1105_MAX_L2_FORWARDING_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	if (!table->entries)
		return -ENOMEM;

	table->entry_count = SJA1105_MAX_L2_FORWARDING_COUNT;

	l2fwd = table->entries;

	/* First 5 entries define the forwarding rules */
	for (i = 0; i < SJA1105_NUM_PORTS; i++) {
		unsigned int upstream = dsa_upstream_port(priv->ds, i);

		for (j = 0; j < SJA1105_NUM_TC; j++)
			l2fwd[i].vlan_pmap[j] = j;

		if (i == upstream)
			continue;

		sja1105_port_allow_traffic(l2fwd, i, upstream, true);
		sja1105_port_allow_traffic(l2fwd, upstream, i, true);
	}
	/* Next 8 entries define VLAN PCP mapping from ingress to egress.
	 * Create a one-to-one mapping.
	 */
	for (i = 0; i < SJA1105_NUM_TC; i++)
		for (j = 0; j < SJA1105_NUM_PORTS; j++)
			l2fwd[SJA1105_NUM_PORTS + i].vlan_pmap[j] = i;

	return 0;
}