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
struct mapped_device {int dummy; } ;
struct hash_cell {struct dm_table* new_map; struct mapped_device* md; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int /*<<< orphan*/  _hash_lock ; 
 int /*<<< orphan*/  dm_get_live_table (struct mapped_device*,int*) ; 
 struct hash_cell* dm_get_mdptr (struct mapped_device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dm_table *dm_get_inactive_table(struct mapped_device *md, int *srcu_idx)
{
	struct hash_cell *hc;
	struct dm_table *table = NULL;

	/* increment rcu count, we don't care about the table pointer */
	dm_get_live_table(md, srcu_idx);

	down_read(&_hash_lock);
	hc = dm_get_mdptr(md);
	if (!hc || hc->md != md) {
		DMWARN("device has been removed from the dev hash table.");
		goto out;
	}

	table = hc->new_map;

out:
	up_read(&_hash_lock);

	return table;
}