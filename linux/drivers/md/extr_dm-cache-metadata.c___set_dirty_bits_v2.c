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
struct dm_cache_metadata {int changed; int /*<<< orphan*/  dirty_root; int /*<<< orphan*/  dirty_info; int /*<<< orphan*/  cache_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int dm_bitset_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dm_bitset_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned int from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_dirty_callback ; 

__attribute__((used)) static int __set_dirty_bits_v2(struct dm_cache_metadata *cmd, unsigned nr_bits, unsigned long *bits)
{
	int r = 0;

	/* nr_bits is really just a sanity check */
	if (nr_bits != from_cblock(cmd->cache_blocks)) {
		DMERR("dirty bitset is wrong size");
		return -EINVAL;
	}

	r = dm_bitset_del(&cmd->dirty_info, cmd->dirty_root);
	if (r)
		return r;

	cmd->changed = true;
	return dm_bitset_new(&cmd->dirty_info, &cmd->dirty_root, nr_bits, is_dirty_callback, bits);
}