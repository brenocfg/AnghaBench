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
struct hash_cell {int /*<<< orphan*/  uuid_list; int /*<<< orphan*/  md; int /*<<< orphan*/  name_list; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 struct hash_cell* __get_name_cell (char const*) ; 
 struct hash_cell* __get_uuid_cell (char const*) ; 
 int /*<<< orphan*/  _hash_lock ; 
 scalar_t__ _name_buckets ; 
 scalar_t__ _uuid_buckets ; 
 struct hash_cell* alloc_cell (char const*,char const*,struct mapped_device*) ; 
 int /*<<< orphan*/  dm_get (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_hash_cells_mutex ; 
 int /*<<< orphan*/  dm_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_set_mdptr (struct mapped_device*,struct hash_cell*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_cell (struct hash_cell*) ; 
 scalar_t__ hash_str (char const*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm_hash_insert(const char *name, const char *uuid, struct mapped_device *md)
{
	struct hash_cell *cell, *hc;

	/*
	 * Allocate the new cells.
	 */
	cell = alloc_cell(name, uuid, md);
	if (!cell)
		return -ENOMEM;

	/*
	 * Insert the cell into both hash tables.
	 */
	down_write(&_hash_lock);
	hc = __get_name_cell(name);
	if (hc) {
		dm_put(hc->md);
		goto bad;
	}

	list_add(&cell->name_list, _name_buckets + hash_str(name));

	if (uuid) {
		hc = __get_uuid_cell(uuid);
		if (hc) {
			list_del(&cell->name_list);
			dm_put(hc->md);
			goto bad;
		}
		list_add(&cell->uuid_list, _uuid_buckets + hash_str(uuid));
	}
	dm_get(md);
	mutex_lock(&dm_hash_cells_mutex);
	dm_set_mdptr(md, cell);
	mutex_unlock(&dm_hash_cells_mutex);
	up_write(&_hash_lock);

	return 0;

 bad:
	up_write(&_hash_lock);
	free_cell(cell);
	return -EBUSY;
}