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
struct i915_buddy_mm {int const max_order; } ;
struct i915_buddy_block {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct i915_buddy_block*) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct i915_buddy_block*) ; 
 int /*<<< orphan*/  blocks ; 
 struct i915_buddy_block* i915_buddy_alloc (struct i915_buddy_mm*,int) ; 
 int /*<<< orphan*/  i915_buddy_fini (struct i915_buddy_mm*) ; 
 int /*<<< orphan*/  i915_buddy_free_list (struct i915_buddy_mm*,int /*<<< orphan*/ *) ; 
 int i915_buddy_init (struct i915_buddy_mm*,int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int igt_buddy_alloc_optimistic(void *arg)
{
	const int max_order = 16;
	struct i915_buddy_block *block;
	struct i915_buddy_mm mm;
	LIST_HEAD(blocks);
	int order;
	int err;

	/*
	 * Create a mm with one block of each order available, and
	 * try to allocate them all.
	 */

	err = i915_buddy_init(&mm,
			      PAGE_SIZE * ((1 << (max_order + 1)) - 1),
			      PAGE_SIZE);
	if (err) {
		pr_err("buddy_init failed(%d)\n", err);
		return err;
	}
	GEM_BUG_ON(mm.max_order != max_order);

	for (order = 0; order <= max_order; order++) {
		block = i915_buddy_alloc(&mm, order);
		if (IS_ERR(block)) {
			pr_info("buddy_alloc hit -ENOMEM with order=%d\n",
				order);
			err = PTR_ERR(block);
			goto err;
		}

		list_add_tail(&block->link, &blocks);
	}

	/* Should be completely full! */
	block = i915_buddy_alloc(&mm, 0);
	if (!IS_ERR(block)) {
		pr_info("buddy_alloc unexpectedly succeeded, it should be full!");
		list_add_tail(&block->link, &blocks);
		err = -EINVAL;
		goto err;
	}

err:
	i915_buddy_free_list(&mm, &blocks);
	i915_buddy_fini(&mm);
	return err;
}