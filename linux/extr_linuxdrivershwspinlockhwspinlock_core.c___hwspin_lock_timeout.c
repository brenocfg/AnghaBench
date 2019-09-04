#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hwspinlock {TYPE_2__* bank; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* relax ) (struct hwspinlock*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int __hwspin_trylock (struct hwspinlock*,int,unsigned long*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct hwspinlock*) ; 
 scalar_t__ time_is_before_eq_jiffies (unsigned long) ; 

int __hwspin_lock_timeout(struct hwspinlock *hwlock, unsigned int to,
					int mode, unsigned long *flags)
{
	int ret;
	unsigned long expire;

	expire = msecs_to_jiffies(to) + jiffies;

	for (;;) {
		/* Try to take the hwspinlock */
		ret = __hwspin_trylock(hwlock, mode, flags);
		if (ret != -EBUSY)
			break;

		/*
		 * The lock is already taken, let's check if the user wants
		 * us to try again
		 */
		if (time_is_before_eq_jiffies(expire))
			return -ETIMEDOUT;

		/*
		 * Allow platform-specific relax handlers to prevent
		 * hogging the interconnect (no sleeping, though)
		 */
		if (hwlock->bank->ops->relax)
			hwlock->bank->ops->relax(hwlock);
	}

	return ret;
}