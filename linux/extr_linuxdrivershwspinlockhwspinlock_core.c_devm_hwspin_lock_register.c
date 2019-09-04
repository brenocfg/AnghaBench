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
struct hwspinlock_ops {int dummy; } ;
struct hwspinlock_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_hwspin_lock_unreg ; 
 int /*<<< orphan*/  devres_add (struct device*,struct hwspinlock_device**) ; 
 struct hwspinlock_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct hwspinlock_device**) ; 
 int hwspin_lock_register (struct hwspinlock_device*,struct device*,struct hwspinlock_ops const*,int,int) ; 

int devm_hwspin_lock_register(struct device *dev,
			      struct hwspinlock_device *bank,
			      const struct hwspinlock_ops *ops,
			      int base_id, int num_locks)
{
	struct hwspinlock_device **ptr;
	int ret;

	ptr = devres_alloc(devm_hwspin_lock_unreg, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = hwspin_lock_register(bank, dev, ops, base_id, num_locks);
	if (!ret) {
		*ptr = bank;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return ret;
}