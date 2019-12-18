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
struct dm_clone_metadata {int fail_io; int hydration_done; int /*<<< orphan*/  region_map; int /*<<< orphan*/  nr_regions; scalar_t__ read_only; int /*<<< orphan*/  bitmap_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  nr_words; void* region_size; void* target_size; struct block_device* bdev; } ;
struct block_device {int dummy; } ;
typedef  void* sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMERR (char*) ; 
 int ENOMEM ; 
 struct dm_clone_metadata* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __create_persistent_data_structures (struct dm_clone_metadata*,int) ; 
 int /*<<< orphan*/  __destroy_persistent_data_structures (struct dm_clone_metadata*) ; 
 int __load_bitset_in_core (struct dm_clone_metadata*) ; 
 scalar_t__ bitmap_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_size (int /*<<< orphan*/ ) ; 
 int dirty_map_init (struct dm_clone_metadata*) ; 
 int /*<<< orphan*/  dm_sector_div_up (void*,void*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_clone_metadata*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dm_clone_metadata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct dm_clone_metadata *dm_clone_metadata_open(struct block_device *bdev,
						 sector_t target_size,
						 sector_t region_size)
{
	int r;
	struct dm_clone_metadata *cmd;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		DMERR("Failed to allocate memory for dm-clone metadata");
		return ERR_PTR(-ENOMEM);
	}

	cmd->bdev = bdev;
	cmd->target_size = target_size;
	cmd->region_size = region_size;
	cmd->nr_regions = dm_sector_div_up(cmd->target_size, cmd->region_size);
	cmd->nr_words = BITS_TO_LONGS(cmd->nr_regions);

	init_rwsem(&cmd->lock);
	spin_lock_init(&cmd->bitmap_lock);
	cmd->read_only = 0;
	cmd->fail_io = false;
	cmd->hydration_done = false;

	cmd->region_map = kvmalloc(bitmap_size(cmd->nr_regions), GFP_KERNEL);
	if (!cmd->region_map) {
		DMERR("Failed to allocate memory for region bitmap");
		r = -ENOMEM;
		goto out_with_md;
	}

	r = __create_persistent_data_structures(cmd, true);
	if (r)
		goto out_with_region_map;

	r = __load_bitset_in_core(cmd);
	if (r) {
		DMERR("Failed to load on-disk region map");
		goto out_with_pds;
	}

	r = dirty_map_init(cmd);
	if (r)
		goto out_with_pds;

	if (bitmap_full(cmd->region_map, cmd->nr_regions))
		cmd->hydration_done = true;

	return cmd;

out_with_pds:
	__destroy_persistent_data_structures(cmd);

out_with_region_map:
	kvfree(cmd->region_map);

out_with_md:
	kfree(cmd);

	return ERR_PTR(r);
}