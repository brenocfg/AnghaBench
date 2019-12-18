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
typedef  int /*<<< orphan*/  u64 ;
struct i915_syncmap {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  height; struct i915_syncmap* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (unsigned int) ; 
 int EINVAL ; 
 scalar_t__ SHIFT ; 
 size_t __sync_branch_idx (struct i915_syncmap*,int /*<<< orphan*/ ) ; 
 struct i915_syncmap** __sync_child (struct i915_syncmap*) ; 
 int check_leaf (struct i915_syncmap**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dump_syncmap (struct i915_syncmap*,int) ; 
 int hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_syncmap_init (struct i915_syncmap**) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int igt_syncmap_join_above(void *arg)
{
	struct i915_syncmap *sync;
	unsigned int pass, order;
	int err;

	i915_syncmap_init(&sync);

	/*
	 * When we have a new id that doesn't fit inside the existing tree,
	 * we need to add a new layer above.
	 *
	 * 1: 0x00000001
	 * 2: 0x00000010
	 * 3: 0x00000100
	 * 4: 0x00001000
	 * ...
	 * Each pass the common prefix shrinks and we have to insert a join.
	 * Each join will only contain two branches, the latest of which
	 * is always a leaf.
	 *
	 * If we then reuse the same set of contexts, we expect to build an
	 * identical tree.
	 */
	for (pass = 0; pass < 3; pass++) {
		for (order = 0; order < 64; order += SHIFT) {
			u64 context = BIT_ULL(order);
			struct i915_syncmap *join;

			err = check_leaf(&sync, context, 0);
			if (err)
				goto out;

			join = sync->parent;
			if (!join) /* very first insert will have no parents */
				continue;

			if (!join->height) {
				pr_err("Parent with no height!\n");
				err = -EINVAL;
				goto out;
			}

			if (hweight32(join->bitmap) != 2) {
				pr_err("Join does not have 2 children: %x (%d)\n",
				       join->bitmap, hweight32(join->bitmap));
				err = -EINVAL;
				goto out;
			}

			if (__sync_child(join)[__sync_branch_idx(join, context)] != sync) {
				pr_err("Leaf misplaced in parent!\n");
				err = -EINVAL;
				goto out;
			}
		}
	}
out:
	return dump_syncmap(sync, err);
}