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
struct skl_ddb_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ skl_ddb_entries_overlap (struct skl_ddb_entry const*,struct skl_ddb_entry const*) ; 

bool skl_ddb_allocation_overlaps(const struct skl_ddb_entry *ddb,
				 const struct skl_ddb_entry *entries,
				 int num_entries, int ignore_idx)
{
	int i;

	for (i = 0; i < num_entries; i++) {
		if (i != ignore_idx &&
		    skl_ddb_entries_overlap(ddb, &entries[i]))
			return true;
	}

	return false;
}