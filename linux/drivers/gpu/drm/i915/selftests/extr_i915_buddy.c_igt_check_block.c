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
typedef  int u64 ;
struct i915_buddy_mm {int chunk_size; } ;
struct i915_buddy_block {scalar_t__ parent; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int I915_BUDDY_ALLOCATED ; 
 unsigned int I915_BUDDY_FREE ; 
 unsigned int I915_BUDDY_SPLIT ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 struct i915_buddy_block* get_buddy (struct i915_buddy_block*) ; 
 int i915_buddy_block_offset (struct i915_buddy_block*) ; 
 int i915_buddy_block_size (struct i915_buddy_mm*,struct i915_buddy_block*) ; 
 unsigned int i915_buddy_block_state (struct i915_buddy_block*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int igt_check_block(struct i915_buddy_mm *mm,
			   struct i915_buddy_block *block)
{
	struct i915_buddy_block *buddy;
	unsigned int block_state;
	u64 block_size;
	u64 offset;
	int err = 0;

	block_state = i915_buddy_block_state(block);

	if (block_state != I915_BUDDY_ALLOCATED &&
	    block_state != I915_BUDDY_FREE &&
	    block_state != I915_BUDDY_SPLIT) {
		pr_err("block state mismatch\n");
		err = -EINVAL;
	}

	block_size = i915_buddy_block_size(mm, block);
	offset = i915_buddy_block_offset(block);

	if (block_size < mm->chunk_size) {
		pr_err("block size smaller than min size\n");
		err = -EINVAL;
	}

	if (!is_power_of_2(block_size)) {
		pr_err("block size not power of two\n");
		err = -EINVAL;
	}

	if (!IS_ALIGNED(block_size, mm->chunk_size)) {
		pr_err("block size not aligned to min size\n");
		err = -EINVAL;
	}

	if (!IS_ALIGNED(offset, mm->chunk_size)) {
		pr_err("block offset not aligned to min size\n");
		err = -EINVAL;
	}

	if (!IS_ALIGNED(offset, block_size)) {
		pr_err("block offset not aligned to block size\n");
		err = -EINVAL;
	}

	buddy = get_buddy(block);

	if (!buddy && block->parent) {
		pr_err("buddy has gone fishing\n");
		err = -EINVAL;
	}

	if (buddy) {
		if (i915_buddy_block_offset(buddy) != (offset ^ block_size)) {
			pr_err("buddy has wrong offset\n");
			err = -EINVAL;
		}

		if (i915_buddy_block_size(mm, buddy) != block_size) {
			pr_err("buddy size mismatch\n");
			err = -EINVAL;
		}

		if (i915_buddy_block_state(buddy) == block_state &&
		    block_state == I915_BUDDY_FREE) {
			pr_err("block and its buddy are free\n");
			err = -EINVAL;
		}
	}

	return err;
}