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
 int EINVAL ; 
 int hwlock_to_id (struct hwspinlock*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int hwspin_lock_get_id(struct hwspinlock *hwlock)
{
	if (!hwlock) {
		pr_err("invalid hwlock\n");
		return -EINVAL;
	}

	return hwlock_to_id(hwlock);
}