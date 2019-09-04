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
 int /*<<< orphan*/  hwspinlock_tree ; 
 int /*<<< orphan*/  hwspinlock_tree_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int radix_tree_gang_lookup_tag (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct hwspinlock *hwspin_lock_request(void)
{
	struct hwspinlock *hwlock;
	int ret;

	mutex_lock(&hwspinlock_tree_lock);

	/* look for an unused lock */
	ret = radix_tree_gang_lookup_tag(&hwspinlock_tree, (void **)&hwlock,
						0, 1, HWSPINLOCK_UNUSED);
	if (ret == 0) {
		pr_warn("a free hwspinlock is not available\n");
		hwlock = NULL;
		goto out;
	}

	/* sanity check that should never fail */
	WARN_ON(ret > 1);

	/* mark as used and power up */
	ret = __hwspin_lock_request(hwlock);
	if (ret < 0)
		hwlock = NULL;

out:
	mutex_unlock(&hwspinlock_tree_lock);
	return hwlock;
}