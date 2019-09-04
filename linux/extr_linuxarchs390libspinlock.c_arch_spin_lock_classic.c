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
 int /*<<< orphan*/  MACHINE_IS_LPAR ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int SPINLOCK_LOCKVAL ; 
 int _Q_LOCK_CPU_MASK ; 
 int _Q_TAIL_MASK ; 
 scalar_t__ arch_cmpxchg_niai8 (int /*<<< orphan*/ *,int,int) ; 
 int arch_load_niai4 (int /*<<< orphan*/ *) ; 
 int arch_spin_yield_target (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ arch_vcpu_is_preempted (int) ; 
 int /*<<< orphan*/  smp_yield_cpu (int) ; 
 int spin_retry ; 

__attribute__((used)) static inline void arch_spin_lock_classic(arch_spinlock_t *lp)
{
	int lockval, old, new, owner, count;

	lockval = SPINLOCK_LOCKVAL;	/* cpu + 1 */

	/* Pass the virtual CPU to the lock holder if it is not running */
	owner = arch_spin_yield_target(READ_ONCE(lp->lock), NULL);
	if (owner && arch_vcpu_is_preempted(owner - 1))
		smp_yield_cpu(owner - 1);

	count = spin_retry;
	while (1) {
		old = arch_load_niai4(&lp->lock);
		owner = old & _Q_LOCK_CPU_MASK;
		/* Try to get the lock if it is free. */
		if (!owner) {
			new = (old & _Q_TAIL_MASK) | lockval;
			if (arch_cmpxchg_niai8(&lp->lock, old, new)) {
				/* Got the lock */
				return;
			}
			continue;
		}
		if (count-- >= 0)
			continue;
		count = spin_retry;
		if (!MACHINE_IS_LPAR || arch_vcpu_is_preempted(owner - 1))
			smp_yield_cpu(owner - 1);
	}
}