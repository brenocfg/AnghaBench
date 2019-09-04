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
 int /*<<< orphan*/  HWSPINLOCK_UNUSED ; 
 int /*<<< orphan*/  hwspinlock_tree ; 
 int /*<<< orphan*/  hwspinlock_tree_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 struct hwspinlock* radix_tree_delete (int /*<<< orphan*/ *,unsigned int) ; 
 int radix_tree_tag_get (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hwspinlock *hwspin_lock_unregister_single(unsigned int id)
{
	struct hwspinlock *hwlock = NULL;
	int ret;

	mutex_lock(&hwspinlock_tree_lock);

	/* make sure the hwspinlock is not in use (tag is set) */
	ret = radix_tree_tag_get(&hwspinlock_tree, id, HWSPINLOCK_UNUSED);
	if (ret == 0) {
		pr_err("hwspinlock %d still in use (or not present)\n", id);
		goto out;
	}

	hwlock = radix_tree_delete(&hwspinlock_tree, id);
	if (!hwlock) {
		pr_err("failed to delete hwspinlock %d\n", id);
		goto out;
	}

out:
	mutex_unlock(&hwspinlock_tree_lock);
	return hwlock;
}