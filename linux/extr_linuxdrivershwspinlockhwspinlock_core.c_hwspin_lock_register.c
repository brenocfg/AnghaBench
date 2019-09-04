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
struct hwspinlock_ops {int /*<<< orphan*/  unlock; int /*<<< orphan*/  trylock; } ;
struct hwspinlock_device {int base_id; int num_locks; struct hwspinlock* lock; struct hwspinlock_ops const* ops; struct device* dev; } ;
struct hwspinlock {struct hwspinlock_device* bank; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int hwspin_lock_register_single (struct hwspinlock*,int) ; 
 int /*<<< orphan*/  hwspin_lock_unregister_single (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hwspin_lock_register(struct hwspinlock_device *bank, struct device *dev,
		const struct hwspinlock_ops *ops, int base_id, int num_locks)
{
	struct hwspinlock *hwlock;
	int ret = 0, i;

	if (!bank || !ops || !dev || !num_locks || !ops->trylock ||
							!ops->unlock) {
		pr_err("invalid parameters\n");
		return -EINVAL;
	}

	bank->dev = dev;
	bank->ops = ops;
	bank->base_id = base_id;
	bank->num_locks = num_locks;

	for (i = 0; i < num_locks; i++) {
		hwlock = &bank->lock[i];

		spin_lock_init(&hwlock->lock);
		hwlock->bank = bank;

		ret = hwspin_lock_register_single(hwlock, base_id + i);
		if (ret)
			goto reg_failed;
	}

	return 0;

reg_failed:
	while (--i >= 0)
		hwspin_lock_unregister_single(base_id + i);
	return ret;
}