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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 scalar_t__ READ_ONCE (scalar_t__) ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ in_nmi () ; 
 int /*<<< orphan*/  lock_kicker_irq ; 
 int /*<<< orphan*/ * this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_clear_irq_pending (int) ; 
 int /*<<< orphan*/  xen_poll_irq (int) ; 
 int /*<<< orphan*/  xen_qlock_wait_nest ; 
 scalar_t__ xen_test_irq_pending (int) ; 

__attribute__((used)) static void xen_qlock_wait(u8 *byte, u8 val)
{
	int irq = __this_cpu_read(lock_kicker_irq);
	atomic_t *nest_cnt = this_cpu_ptr(&xen_qlock_wait_nest);

	/* If kicker interrupts not initialized yet, just spin */
	if (irq == -1 || in_nmi())
		return;

	/* Detect reentry. */
	atomic_inc(nest_cnt);

	/* If irq pending already and no nested call clear it. */
	if (atomic_read(nest_cnt) == 1 && xen_test_irq_pending(irq)) {
		xen_clear_irq_pending(irq);
	} else if (READ_ONCE(*byte) == val) {
		/* Block until irq becomes pending (or a spurious wakeup) */
		xen_poll_irq(irq);
	}

	atomic_dec(nest_cnt);
}