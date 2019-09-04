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
struct hwspinlock_device {int num_locks; scalar_t__ base_id; struct hwspinlock* lock; } ;
struct hwspinlock {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct hwspinlock* hwspin_lock_unregister_single (scalar_t__) ; 

int hwspin_lock_unregister(struct hwspinlock_device *bank)
{
	struct hwspinlock *hwlock, *tmp;
	int i;

	for (i = 0; i < bank->num_locks; i++) {
		hwlock = &bank->lock[i];

		tmp = hwspin_lock_unregister_single(bank->base_id + i);
		if (!tmp)
			return -EBUSY;

		/* self-sanity check that should never fail */
		WARN_ON(tmp != hwlock);
	}

	return 0;
}