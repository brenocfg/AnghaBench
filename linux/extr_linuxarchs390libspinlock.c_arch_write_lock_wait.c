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
struct TYPE_3__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  cnts; } ;
typedef  TYPE_1__ arch_rwlock_t ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ __atomic_cmpxchg_bool (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 

void arch_write_lock_wait(arch_rwlock_t *rw)
{
	int old;

	/* Add this CPU to the write waiters */
	__atomic_add(0x20000, &rw->cnts);

	/* Put the writer into the wait queue */
	arch_spin_lock(&rw->wait);

	while (1) {
		old = READ_ONCE(rw->cnts);
		if ((old & 0x1ffff) == 0 &&
		    __atomic_cmpxchg_bool(&rw->cnts, old, old | 0x10000))
			/* Got the lock */
			break;
		barrier();
	}

	arch_spin_unlock(&rw->wait);
}