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
struct target_type {int /*<<< orphan*/  name; } ;
struct mapped_device {int dummy; } ;
struct hash_cell {struct dm_table* new_map; struct mapped_device* md; } ;
struct file {int dummy; } ;
struct dm_table {int dummy; } ;
struct dm_ioctl {int /*<<< orphan*/  flags; int /*<<< orphan*/  target_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,...) ; 
 int /*<<< orphan*/  DM_INACTIVE_PRESENT_FLAG ; 
 scalar_t__ DM_TYPE_NONE ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  __dev_status (struct mapped_device*,struct dm_ioctl*) ; 
 int /*<<< orphan*/  _hash_lock ; 
 struct target_type* dm_get_immutable_target_type (struct mapped_device*) ; 
 scalar_t__ dm_get_md_type (struct mapped_device*) ; 
 struct hash_cell* dm_get_mdptr (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_lock_md_type (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_set_md_type (struct mapped_device*,int /*<<< orphan*/ ) ; 
 int dm_setup_md_queue (struct mapped_device*,struct dm_table*) ; 
 int /*<<< orphan*/  dm_sync_table (struct mapped_device*) ; 
 int dm_table_create (struct dm_table**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_destroy (struct dm_table*) ; 
 struct target_type* dm_table_get_immutable_target_type (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_get_type (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_get_wildcard_target (struct dm_table*) ; 
 int /*<<< orphan*/  dm_unlock_md_type (struct mapped_device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct mapped_device* find_device (struct dm_ioctl*) ; 
 int /*<<< orphan*/  get_mode (struct dm_ioctl*) ; 
 int /*<<< orphan*/  is_valid_type (scalar_t__,int /*<<< orphan*/ ) ; 
 int populate_table (struct dm_table*,struct dm_ioctl*,size_t) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int table_load(struct file *filp, struct dm_ioctl *param, size_t param_size)
{
	int r;
	struct hash_cell *hc;
	struct dm_table *t, *old_map = NULL;
	struct mapped_device *md;
	struct target_type *immutable_target_type;

	md = find_device(param);
	if (!md)
		return -ENXIO;

	r = dm_table_create(&t, get_mode(param), param->target_count, md);
	if (r)
		goto err;

	/* Protect md->type and md->queue against concurrent table loads. */
	dm_lock_md_type(md);
	r = populate_table(t, param, param_size);
	if (r)
		goto err_unlock_md_type;

	immutable_target_type = dm_get_immutable_target_type(md);
	if (immutable_target_type &&
	    (immutable_target_type != dm_table_get_immutable_target_type(t)) &&
	    !dm_table_get_wildcard_target(t)) {
		DMWARN("can't replace immutable target type %s",
		       immutable_target_type->name);
		r = -EINVAL;
		goto err_unlock_md_type;
	}

	if (dm_get_md_type(md) == DM_TYPE_NONE) {
		/* Initial table load: acquire type of table. */
		dm_set_md_type(md, dm_table_get_type(t));

		/* setup md->queue to reflect md's type (may block) */
		r = dm_setup_md_queue(md, t);
		if (r) {
			DMWARN("unable to set up device queue for new table.");
			goto err_unlock_md_type;
		}
	} else if (!is_valid_type(dm_get_md_type(md), dm_table_get_type(t))) {
		DMWARN("can't change device type (old=%u vs new=%u) after initial table load.",
		       dm_get_md_type(md), dm_table_get_type(t));
		r = -EINVAL;
		goto err_unlock_md_type;
	}

	dm_unlock_md_type(md);

	/* stage inactive table */
	down_write(&_hash_lock);
	hc = dm_get_mdptr(md);
	if (!hc || hc->md != md) {
		DMWARN("device has been removed from the dev hash table.");
		up_write(&_hash_lock);
		r = -ENXIO;
		goto err_destroy_table;
	}

	if (hc->new_map)
		old_map = hc->new_map;
	hc->new_map = t;
	up_write(&_hash_lock);

	param->flags |= DM_INACTIVE_PRESENT_FLAG;
	__dev_status(md, param);

	if (old_map) {
		dm_sync_table(md);
		dm_table_destroy(old_map);
	}

	dm_put(md);

	return 0;

err_unlock_md_type:
	dm_unlock_md_type(md);
err_destroy_table:
	dm_table_destroy(t);
err:
	dm_put(md);

	return r;
}