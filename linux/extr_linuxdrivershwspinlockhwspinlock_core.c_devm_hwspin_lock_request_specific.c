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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_hwspin_lock_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct hwspinlock**) ; 
 struct hwspinlock** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct hwspinlock**) ; 
 struct hwspinlock* hwspin_lock_request_specific (unsigned int) ; 

struct hwspinlock *devm_hwspin_lock_request_specific(struct device *dev,
						     unsigned int id)
{
	struct hwspinlock **ptr, *hwlock;

	ptr = devres_alloc(devm_hwspin_lock_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return NULL;

	hwlock = hwspin_lock_request_specific(id);
	if (hwlock) {
		*ptr = hwlock;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return hwlock;
}