#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ arch_spinlock_t ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int SPINLOCK_LOCKVAL ; 
 scalar_t__ __atomic_cmpxchg_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int spin_retry ; 

int arch_spin_trylock_retry(arch_spinlock_t *lp)
{
	int cpu = SPINLOCK_LOCKVAL;
	int owner, count;

	for (count = spin_retry; count > 0; count--) {
		owner = READ_ONCE(lp->lock);
		/* Try to get the lock if it is free. */
		if (!owner) {
			if (__atomic_cmpxchg_bool(&lp->lock, 0, cpu))
				return 1;
		}
	}
	return 0;
}