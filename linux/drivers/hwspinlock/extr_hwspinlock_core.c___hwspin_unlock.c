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
struct hwspinlock {int /*<<< orphan*/  lock; TYPE_2__* bank; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unlock ) (struct hwspinlock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  HWLOCK_IN_ATOMIC 131 
#define  HWLOCK_IRQ 130 
#define  HWLOCK_IRQSTATE 129 
#define  HWLOCK_RAW 128 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct hwspinlock*) ; 

void __hwspin_unlock(struct hwspinlock *hwlock, int mode, unsigned long *flags)
{
	BUG_ON(!hwlock);
	BUG_ON(!flags && mode == HWLOCK_IRQSTATE);

	/*
	 * We must make sure that memory operations (both reads and writes),
	 * done before unlocking the hwspinlock, will not be reordered
	 * after the lock is released.
	 *
	 * That's the purpose of this explicit memory barrier.
	 *
	 * Note: the memory barrier induced by the spin_unlock below is too
	 * late; the other core is going to access memory soon after it will
	 * take the hwspinlock, and by then we want to be sure our memory
	 * operations are already observable.
	 */
	mb();

	hwlock->bank->ops->unlock(hwlock);

	/* Undo the spin_trylock{_irq, _irqsave} called while locking */
	switch (mode) {
	case HWLOCK_IRQSTATE:
		spin_unlock_irqrestore(&hwlock->lock, *flags);
		break;
	case HWLOCK_IRQ:
		spin_unlock_irq(&hwlock->lock);
		break;
	case HWLOCK_RAW:
	case HWLOCK_IN_ATOMIC:
		/* Nothing to do */
		break;
	default:
		spin_unlock(&hwlock->lock);
		break;
	}
}