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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devm_hwspin_lock_match ; 
 int /*<<< orphan*/  devm_hwspin_lock_release ; 
 int devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hwspinlock*) ; 

int devm_hwspin_lock_free(struct device *dev, struct hwspinlock *hwlock)
{
	int ret;

	ret = devres_release(dev, devm_hwspin_lock_release,
			     devm_hwspin_lock_match, hwlock);
	WARN_ON(ret);

	return ret;
}