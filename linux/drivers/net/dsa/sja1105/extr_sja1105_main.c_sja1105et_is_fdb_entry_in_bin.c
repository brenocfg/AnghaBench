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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sja1105_private {int dummy; } ;
struct sja1105_l2_lookup_entry {scalar_t__ macaddr; scalar_t__ vlanid; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_IDX_L2_LOOKUP ; 
 int SJA1105ET_FDB_BIN_SIZE ; 
 scalar_t__ ether_addr_to_u64 (int /*<<< orphan*/  const*) ; 
 scalar_t__ sja1105_dynamic_config_read (struct sja1105_private*,int /*<<< orphan*/ ,int,struct sja1105_l2_lookup_entry*) ; 
 int sja1105et_fdb_index (int,int) ; 

__attribute__((used)) static int sja1105et_is_fdb_entry_in_bin(struct sja1105_private *priv, int bin,
					 const u8 *addr, u16 vid,
					 struct sja1105_l2_lookup_entry *match,
					 int *last_unused)
{
	int way;

	for (way = 0; way < SJA1105ET_FDB_BIN_SIZE; way++) {
		struct sja1105_l2_lookup_entry l2_lookup = {0};
		int index = sja1105et_fdb_index(bin, way);

		/* Skip unused entries, optionally marking them
		 * into the return value
		 */
		if (sja1105_dynamic_config_read(priv, BLK_IDX_L2_LOOKUP,
						index, &l2_lookup)) {
			if (last_unused)
				*last_unused = way;
			continue;
		}

		if (l2_lookup.macaddr == ether_addr_to_u64(addr) &&
		    l2_lookup.vlanid == vid) {
			if (match)
				*match = l2_lookup;
			return way;
		}
	}
	/* Return an invalid entry index if not found */
	return -1;
}