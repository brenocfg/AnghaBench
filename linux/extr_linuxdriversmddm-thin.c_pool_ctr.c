#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pool_features {scalar_t__ mode; scalar_t__ discard_enabled; scalar_t__ discard_passdown; } ;
struct TYPE_6__ {int /*<<< orphan*/  congested_fn; } ;
struct pool_c {TYPE_3__ callbacks; struct pool* pool; struct pool_features requested_pf; struct pool_features adjusted_pf; scalar_t__ low_water_blocks; struct dm_dev* data_dev; struct dm_dev* metadata_dev; struct dm_target* ti; } ;
struct TYPE_4__ {scalar_t__ discard_enabled; } ;
struct pool {int /*<<< orphan*/  pmd; TYPE_1__ pf; } ;
struct dm_target {char* error; int num_flush_bios; int num_discard_bios; int discards_supported; int /*<<< orphan*/  table; struct pool_c* private; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;
struct dm_arg_set {unsigned int argc; char** argv; } ;
typedef  int fmode_t ;
typedef  scalar_t__ dm_block_t ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 unsigned long DATA_DEV_BLOCK_SIZE_MAX_SECTORS ; 
 unsigned long DATA_DEV_BLOCK_SIZE_MIN_SECTORS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pool*) ; 
 scalar_t__ PM_READ_ONLY ; 
 int PTR_ERR (struct pool*) ; 
 int /*<<< orphan*/  __pool_dec (struct pool*) ; 
 struct pool* __pool_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,char**,int*) ; 
 int /*<<< orphan*/  calc_metadata_threshold (struct pool_c*) ; 
 int /*<<< orphan*/  dm_consume_args (struct dm_arg_set*,int) ; 
 int dm_get_device (struct dm_target*,char*,int,struct dm_dev**) ; 
 int dm_pool_register_metadata_threshold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pool*) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,struct dm_dev*) ; 
 int /*<<< orphan*/  dm_table_add_target_callbacks (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dm_table_get_md (int /*<<< orphan*/ ) ; 
 TYPE_2__ dm_thin_pool_table ; 
 int /*<<< orphan*/  kfree (struct pool_c*) ; 
 scalar_t__ kstrtoul (char*,int,unsigned long*) ; 
 scalar_t__ kstrtoull (char*,int,unsigned long long*) ; 
 struct pool_c* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_low_callback ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int parse_pool_features (struct dm_arg_set*,struct pool_features*,struct dm_target*) ; 
 int /*<<< orphan*/  pool_features_init (struct pool_features*) ; 
 int /*<<< orphan*/  pool_is_congested ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  warn_if_metadata_device_too_big (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pool_ctr(struct dm_target *ti, unsigned argc, char **argv)
{
	int r, pool_created = 0;
	struct pool_c *pt;
	struct pool *pool;
	struct pool_features pf;
	struct dm_arg_set as;
	struct dm_dev *data_dev;
	unsigned long block_size;
	dm_block_t low_water_blocks;
	struct dm_dev *metadata_dev;
	fmode_t metadata_mode;

	/*
	 * FIXME Remove validation from scope of lock.
	 */
	mutex_lock(&dm_thin_pool_table.mutex);

	if (argc < 4) {
		ti->error = "Invalid argument count";
		r = -EINVAL;
		goto out_unlock;
	}

	as.argc = argc;
	as.argv = argv;

	/* make sure metadata and data are different devices */
	if (!strcmp(argv[0], argv[1])) {
		ti->error = "Error setting metadata or data device";
		r = -EINVAL;
		goto out_unlock;
	}

	/*
	 * Set default pool features.
	 */
	pool_features_init(&pf);

	dm_consume_args(&as, 4);
	r = parse_pool_features(&as, &pf, ti);
	if (r)
		goto out_unlock;

	metadata_mode = FMODE_READ | ((pf.mode == PM_READ_ONLY) ? 0 : FMODE_WRITE);
	r = dm_get_device(ti, argv[0], metadata_mode, &metadata_dev);
	if (r) {
		ti->error = "Error opening metadata block device";
		goto out_unlock;
	}
	warn_if_metadata_device_too_big(metadata_dev->bdev);

	r = dm_get_device(ti, argv[1], FMODE_READ | FMODE_WRITE, &data_dev);
	if (r) {
		ti->error = "Error getting data device";
		goto out_metadata;
	}

	if (kstrtoul(argv[2], 10, &block_size) || !block_size ||
	    block_size < DATA_DEV_BLOCK_SIZE_MIN_SECTORS ||
	    block_size > DATA_DEV_BLOCK_SIZE_MAX_SECTORS ||
	    block_size & (DATA_DEV_BLOCK_SIZE_MIN_SECTORS - 1)) {
		ti->error = "Invalid block size";
		r = -EINVAL;
		goto out;
	}

	if (kstrtoull(argv[3], 10, (unsigned long long *)&low_water_blocks)) {
		ti->error = "Invalid low water mark";
		r = -EINVAL;
		goto out;
	}

	pt = kzalloc(sizeof(*pt), GFP_KERNEL);
	if (!pt) {
		r = -ENOMEM;
		goto out;
	}

	pool = __pool_find(dm_table_get_md(ti->table), metadata_dev->bdev,
			   block_size, pf.mode == PM_READ_ONLY, &ti->error, &pool_created);
	if (IS_ERR(pool)) {
		r = PTR_ERR(pool);
		goto out_free_pt;
	}

	/*
	 * 'pool_created' reflects whether this is the first table load.
	 * Top level discard support is not allowed to be changed after
	 * initial load.  This would require a pool reload to trigger thin
	 * device changes.
	 */
	if (!pool_created && pf.discard_enabled != pool->pf.discard_enabled) {
		ti->error = "Discard support cannot be disabled once enabled";
		r = -EINVAL;
		goto out_flags_changed;
	}

	pt->pool = pool;
	pt->ti = ti;
	pt->metadata_dev = metadata_dev;
	pt->data_dev = data_dev;
	pt->low_water_blocks = low_water_blocks;
	pt->adjusted_pf = pt->requested_pf = pf;
	ti->num_flush_bios = 1;

	/*
	 * Only need to enable discards if the pool should pass
	 * them down to the data device.  The thin device's discard
	 * processing will cause mappings to be removed from the btree.
	 */
	if (pf.discard_enabled && pf.discard_passdown) {
		ti->num_discard_bios = 1;

		/*
		 * Setting 'discards_supported' circumvents the normal
		 * stacking of discard limits (this keeps the pool and
		 * thin devices' discard limits consistent).
		 */
		ti->discards_supported = true;
	}
	ti->private = pt;

	r = dm_pool_register_metadata_threshold(pt->pool->pmd,
						calc_metadata_threshold(pt),
						metadata_low_callback,
						pool);
	if (r)
		goto out_flags_changed;

	pt->callbacks.congested_fn = pool_is_congested;
	dm_table_add_target_callbacks(ti->table, &pt->callbacks);

	mutex_unlock(&dm_thin_pool_table.mutex);

	return 0;

out_flags_changed:
	__pool_dec(pool);
out_free_pt:
	kfree(pt);
out:
	dm_put_device(ti, data_dev);
out_metadata:
	dm_put_device(ti, metadata_dev);
out_unlock:
	mutex_unlock(&dm_thin_pool_table.mutex);

	return r;
}