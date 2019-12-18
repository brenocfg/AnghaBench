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
struct i915_buddy_mm {int dummy; } ;
struct i915_buddy_block {int /*<<< orphan*/  parent; int /*<<< orphan*/  header; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_buddy_block_offset (struct i915_buddy_block*) ; 
 int /*<<< orphan*/  i915_buddy_block_order (struct i915_buddy_block*) ; 
 int /*<<< orphan*/  i915_buddy_block_size (struct i915_buddy_mm*,struct i915_buddy_block*) ; 
 int /*<<< orphan*/  i915_buddy_block_state (struct i915_buddy_block*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int) ; 

__attribute__((used)) static void __igt_dump_block(struct i915_buddy_mm *mm,
			     struct i915_buddy_block *block,
			     bool buddy)
{
	pr_err("block info: header=%llx, state=%u, order=%d, offset=%llx size=%llx root=%s buddy=%s\n",
	       block->header,
	       i915_buddy_block_state(block),
	       i915_buddy_block_order(block),
	       i915_buddy_block_offset(block),
	       i915_buddy_block_size(mm, block),
	       yesno(!block->parent),
	       yesno(buddy));
}