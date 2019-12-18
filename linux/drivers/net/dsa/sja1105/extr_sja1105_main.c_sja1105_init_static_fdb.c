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
struct sja1105_table {scalar_t__ entry_count; int /*<<< orphan*/  entries; } ;
struct TYPE_2__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_1__ static_config; } ;

/* Variables and functions */
 size_t BLK_IDX_L2_LOOKUP ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sja1105_init_static_fdb(struct sja1105_private *priv)
{
	struct sja1105_table *table;

	table = &priv->static_config.tables[BLK_IDX_L2_LOOKUP];

	/* We only populate the FDB table through dynamic
	 * L2 Address Lookup entries
	 */
	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}
	return 0;
}