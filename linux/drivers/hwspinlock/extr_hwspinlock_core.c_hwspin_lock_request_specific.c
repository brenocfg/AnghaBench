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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __hwspin_lock_request (struct hwspinlock*) ; 
 unsigned int hwlock_to_id (struct hwspinlock*) ; 
 int /*<<< orphan*/  hwspinlock_tree ; 
 int /*<<< orphan*/  hwspinlock_tree_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 
 struct hwspinlock* radix_tree_lookup (int /*<<< orphan*/ *,unsigned int) ; 
 int radix_tree_tag_get (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

struct hwspinlock *hwspin_lock_request_specific(unsigned int id)
{
	struct hwspinlock *hwlock;
	int ret;

	mutex_lock(&hwspinlock_tree_lock);

	/* make sure this hwspinlock exists */
	hwlock = radix_tree_lookup(&hwspinlock_tree, id);
	if (!hwlock) {
		pr_warn("hwspinlock %u does not exist\n", id);
		goto out;
	}

	/* sanity check (this shouldn't happen) */
	WARN_ON(hwlock_to_id(hwlock) != id);

	/* make sure this hwspinlock is unused */
	ret = radix_tree_tag_get(&hwspinlock_tree, id, HWSPINLOCK_UNUSED);
	if (ret == 0) {
		pr_warn("hwspinlock %u is already in use\n", id);
		hwlock = NULL;
		goto out;
	}

	/* mark as used and power up */
	ret = __hwspin_lock_request(hwlock);
	if (ret < 0)
		hwlock = NULL;

out:
	mutex_unlock(&hwspinlock_tree_lock);
	return hwlock;
}