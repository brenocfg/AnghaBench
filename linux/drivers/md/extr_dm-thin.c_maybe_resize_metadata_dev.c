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
struct pool_c {struct pool* pool; } ;
struct pool {int /*<<< orphan*/  pmd; int /*<<< orphan*/  pool_md; int /*<<< orphan*/  md_dev; } ;
struct dm_target {struct pool_c* private; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DMINFO (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ PM_OUT_OF_METADATA_SPACE ; 
 int /*<<< orphan*/  PM_WRITE ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 int dm_pool_get_metadata_dev_size (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ dm_pool_metadata_needs_check (int /*<<< orphan*/ ) ; 
 int dm_pool_resize_metadata_dev (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_metadata_dev_size_in_blocks (int /*<<< orphan*/ ) ; 
 scalar_t__ get_pool_mode (struct pool*) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct pool*,char*,int) ; 
 int /*<<< orphan*/  set_pool_mode (struct pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn_if_metadata_device_too_big (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maybe_resize_metadata_dev(struct dm_target *ti, bool *need_commit)
{
	int r;
	struct pool_c *pt = ti->private;
	struct pool *pool = pt->pool;
	dm_block_t metadata_dev_size, sb_metadata_dev_size;

	*need_commit = false;

	metadata_dev_size = get_metadata_dev_size_in_blocks(pool->md_dev);

	r = dm_pool_get_metadata_dev_size(pool->pmd, &sb_metadata_dev_size);
	if (r) {
		DMERR("%s: failed to retrieve metadata device size",
		      dm_device_name(pool->pool_md));
		return r;
	}

	if (metadata_dev_size < sb_metadata_dev_size) {
		DMERR("%s: metadata device (%llu blocks) too small: expected %llu",
		      dm_device_name(pool->pool_md),
		      metadata_dev_size, sb_metadata_dev_size);
		return -EINVAL;

	} else if (metadata_dev_size > sb_metadata_dev_size) {
		if (dm_pool_metadata_needs_check(pool->pmd)) {
			DMERR("%s: unable to grow the metadata device until repaired.",
			      dm_device_name(pool->pool_md));
			return 0;
		}

		warn_if_metadata_device_too_big(pool->md_dev);
		DMINFO("%s: growing the metadata device from %llu to %llu blocks",
		       dm_device_name(pool->pool_md),
		       sb_metadata_dev_size, metadata_dev_size);

		if (get_pool_mode(pool) == PM_OUT_OF_METADATA_SPACE)
			set_pool_mode(pool, PM_WRITE);

		r = dm_pool_resize_metadata_dev(pool->pmd, metadata_dev_size);
		if (r) {
			metadata_operation_failed(pool, "dm_pool_resize_metadata_dev", r);
			return r;
		}

		*need_commit = true;
	}

	return 0;
}