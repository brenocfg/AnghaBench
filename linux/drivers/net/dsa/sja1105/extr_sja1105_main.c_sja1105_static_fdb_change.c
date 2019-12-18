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
struct sja1105_l2_lookup_entry {int dummy; } ;

/* Variables and functions */
 size_t BLK_IDX_L2_LOOKUP ; 
 int sja1105_find_static_fdb_entry (struct sja1105_private*,int,struct sja1105_l2_lookup_entry const*) ; 
 int sja1105_table_resize (struct sja1105_table*,int) ; 

__attribute__((used)) static int
sja1105_static_fdb_change(struct sja1105_private *priv, int port,
			  const struct sja1105_l2_lookup_entry *requested,
			  bool keep)
{
	struct sja1105_l2_lookup_entry *l2_lookup;
	struct sja1105_table *table;
	int rc, match;

	table = &priv->static_config.tables[BLK_IDX_L2_LOOKUP];

	match = sja1105_find_static_fdb_entry(priv, port, requested);
	if (match < 0) {
		/* Can't delete a missing entry. */
		if (!keep)
			return 0;

		/* No match => new entry */
		rc = sja1105_table_resize(table, table->entry_count + 1);
		if (rc)
			return rc;

		match = table->entry_count - 1;
	}

	/* Assign pointer after the resize (it may be new memory) */
	l2_lookup = table->entries;

	/* We have a match.
	 * If the job was to add this FDB entry, it's already done (mostly
	 * anyway, since the port forwarding mask may have changed, case in
	 * which we update it).
	 * Otherwise we have to delete it.
	 */
	if (keep) {
		l2_lookup[match] = *requested;
		return 0;
	}

	/* To remove, the strategy is to overwrite the element with
	 * the last one, and then reduce the array size by 1
	 */
	l2_lookup[match] = l2_lookup[table->entry_count - 1];
	return sja1105_table_resize(table, table->entry_count - 1);
}