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
typedef  unsigned int u64 ;
struct i915_syncmap {unsigned int height; int bitmap; struct i915_syncmap* parent; int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 unsigned int BIT_ULL (unsigned int) ; 
 int EINVAL ; 
 int ENODEV ; 
 unsigned int KSYNCMAP ; 
 unsigned int SHIFT ; 
 struct i915_syncmap** __sync_child (struct i915_syncmap*) ; 
 int check_syncmap_free (struct i915_syncmap**) ; 
 int dump_syncmap (struct i915_syncmap*,int) ; 
 unsigned int hweight32 (int) ; 
 int /*<<< orphan*/  i915_syncmap_init (struct i915_syncmap**) ; 
 int i915_syncmap_set (struct i915_syncmap**,unsigned int,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int igt_syncmap_compact(void *arg)
{
	struct i915_syncmap *sync;
	unsigned int idx, order;
	int err = -ENODEV;

	i915_syncmap_init(&sync);

	/*
	 * The syncmap are "space efficient" compressed radix trees - any
	 * branch with only one child is skipped and replaced by the child.
	 *
	 * If we construct a tree with ids that are neighbouring at a non-zero
	 * height, we form a join but each child of that join is directly a
	 * leaf holding the single id.
	 */
	for (order = SHIFT; order < 64; order += SHIFT) {
		err = check_syncmap_free(&sync);
		if (err)
			goto out;

		/* Create neighbours in the parent */
		for (idx = 0; idx < KSYNCMAP; idx++) {
			u64 context = idx * BIT_ULL(order) + idx;

			err = i915_syncmap_set(&sync, context, 0);
			if (err)
				goto out;

			if (sync->height) {
				pr_err("Inserting context=%llx (order=%d, idx=%d) did not return leaf (height=%d, prefix=%llx\n",
				       context, order, idx,
				       sync->height, sync->prefix);
				err = -EINVAL;
				goto out;
			}
		}

		sync = sync->parent;
		if (sync->parent) {
			pr_err("Parent (join) of last leaf was not the sync!\n");
			err = -EINVAL;
			goto out;
		}

		if (sync->height != order) {
			pr_err("Join does not have the expected height, found %d, expected %d\n",
			       sync->height, order);
			err = -EINVAL;
			goto out;
		}

		if (sync->bitmap != BIT(KSYNCMAP) - 1) {
			pr_err("Join is not full!, found %x (%d) expected %lx (%d)\n",
			       sync->bitmap, hweight32(sync->bitmap),
			       BIT(KSYNCMAP) - 1, KSYNCMAP);
			err = -EINVAL;
			goto out;
		}

		/* Each of our children should be a leaf */
		for (idx = 0; idx < KSYNCMAP; idx++) {
			struct i915_syncmap *leaf = __sync_child(sync)[idx];

			if (leaf->height) {
				pr_err("Child %d is a not leaf!\n", idx);
				err = -EINVAL;
				goto out;
			}

			if (leaf->parent != sync) {
				pr_err("Child %d is not attached to us!\n",
				       idx);
				err = -EINVAL;
				goto out;
			}

			if (!is_power_of_2(leaf->bitmap)) {
				pr_err("Child %d holds more than one id, found %x (%d)\n",
				       idx, leaf->bitmap, hweight32(leaf->bitmap));
				err = -EINVAL;
				goto out;
			}

			if (leaf->bitmap != BIT(idx)) {
				pr_err("Child %d has wrong seqno idx, found %d, expected %d\n",
				       idx, ilog2(leaf->bitmap), idx);
				err = -EINVAL;
				goto out;
			}
		}
	}
out:
	return dump_syncmap(sync, err);
}