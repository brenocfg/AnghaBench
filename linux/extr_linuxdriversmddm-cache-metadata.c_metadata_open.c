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
struct dm_cache_metadata {unsigned int version; size_t policy_hint_size; int changed; int fail_io; scalar_t__ cache_blocks; int /*<<< orphan*/  data_block_size; struct block_device* bdev; int /*<<< orphan*/  root_lock; int /*<<< orphan*/  ref_count; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int ENOMEM ; 
 struct dm_cache_metadata* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __begin_transaction_flags (struct dm_cache_metadata*,int /*<<< orphan*/ ) ; 
 int __create_persistent_data_objects (struct dm_cache_metadata*,int) ; 
 int /*<<< orphan*/  clear_clean_shutdown ; 
 int /*<<< orphan*/  dm_cache_metadata_close (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_cache_metadata*) ; 
 struct dm_cache_metadata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct dm_cache_metadata *metadata_open(struct block_device *bdev,
					       sector_t data_block_size,
					       bool may_format_device,
					       size_t policy_hint_size,
					       unsigned metadata_version)
{
	int r;
	struct dm_cache_metadata *cmd;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		DMERR("could not allocate metadata struct");
		return ERR_PTR(-ENOMEM);
	}

	cmd->version = metadata_version;
	refcount_set(&cmd->ref_count, 1);
	init_rwsem(&cmd->root_lock);
	cmd->bdev = bdev;
	cmd->data_block_size = data_block_size;
	cmd->cache_blocks = 0;
	cmd->policy_hint_size = policy_hint_size;
	cmd->changed = true;
	cmd->fail_io = false;

	r = __create_persistent_data_objects(cmd, may_format_device);
	if (r) {
		kfree(cmd);
		return ERR_PTR(r);
	}

	r = __begin_transaction_flags(cmd, clear_clean_shutdown);
	if (r < 0) {
		dm_cache_metadata_close(cmd);
		return ERR_PTR(r);
	}

	return cmd;
}