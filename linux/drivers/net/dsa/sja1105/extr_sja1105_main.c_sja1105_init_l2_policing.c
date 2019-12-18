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
struct sja1105_table {struct sja1105_l2_policing_entry* entries; scalar_t__ entry_count; TYPE_2__* ops; } ;
struct TYPE_3__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_1__ static_config; } ;
struct sja1105_l2_policing_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  unpacked_entry_size; } ;

/* Variables and functions */
 size_t BLK_IDX_L2_POLICING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SJA1105_MAX_L2_POLICING_COUNT ; 
 int SJA1105_NUM_PORTS ; 
 int SJA1105_NUM_TC ; 
 struct sja1105_l2_policing_entry* kcalloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sja1105_l2_policing_entry*) ; 
 int /*<<< orphan*/  sja1105_setup_policer (struct sja1105_l2_policing_entry*,int) ; 

__attribute__((used)) static int sja1105_init_l2_policing(struct sja1105_private *priv)
{
	struct sja1105_l2_policing_entry *policing;
	struct sja1105_table *table;
	int i, j, k;

	table = &priv->static_config.tables[BLK_IDX_L2_POLICING];

	/* Discard previous L2 Policing Table */
	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	table->entries = kcalloc(SJA1105_MAX_L2_POLICING_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	if (!table->entries)
		return -ENOMEM;

	table->entry_count = SJA1105_MAX_L2_POLICING_COUNT;

	policing = table->entries;

	/* k sweeps through all unicast policers (0-39).
	 * bcast sweeps through policers 40-44.
	 */
	for (i = 0, k = 0; i < SJA1105_NUM_PORTS; i++) {
		int bcast = (SJA1105_NUM_PORTS * SJA1105_NUM_TC) + i;

		for (j = 0; j < SJA1105_NUM_TC; j++, k++)
			sja1105_setup_policer(policing, k);

		/* Set up this port's policer for broadcast traffic */
		sja1105_setup_policer(policing, bcast);
	}
	return 0;
}