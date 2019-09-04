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
struct hwspinlock {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  HWSPINLOCK_UNUSED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hwspinlock_tree ; 
 int /*<<< orphan*/  hwspinlock_tree_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int,struct hwspinlock*) ; 
 struct hwspinlock* radix_tree_tag_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwspin_lock_register_single(struct hwspinlock *hwlock, int id)
{
	struct hwspinlock *tmp;
	int ret;

	mutex_lock(&hwspinlock_tree_lock);

	ret = radix_tree_insert(&hwspinlock_tree, id, hwlock);
	if (ret) {
		if (ret == -EEXIST)
			pr_err("hwspinlock id %d already exists!\n", id);
		goto out;
	}

	/* mark this hwspinlock as available */
	tmp = radix_tree_tag_set(&hwspinlock_tree, id, HWSPINLOCK_UNUSED);

	/* self-sanity check which should never fail */
	WARN_ON(tmp != hwlock);

out:
	mutex_unlock(&hwspinlock_tree_lock);
	return 0;
}