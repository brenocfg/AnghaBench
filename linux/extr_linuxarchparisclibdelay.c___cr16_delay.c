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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ mfctl (int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __cr16_delay(unsigned long __loops)
{
	/*
	 * Note: Due to unsigned math, cr16 rollovers shouldn't be
	 * a problem here. However, on 32 bit, we need to make sure
	 * we don't pass in too big a value. The current default
	 * value of MAX_UDELAY_MS should help prevent this.
	 */
	u32 bclock, now, loops = __loops;
	int cpu;

	preempt_disable();
	cpu = smp_processor_id();
	bclock = mfctl(16);
	for (;;) {
		now = mfctl(16);
		if ((now - bclock) >= loops)
			break;

		/* Allow RT tasks to run */
		preempt_enable();
		asm volatile("	nop\n");
		barrier();
		preempt_disable();

		/*
		 * It is possible that we moved to another CPU, and
		 * since CR16's are per-cpu we need to calculate
		 * that. The delay must guarantee that we wait "at
		 * least" the amount of time. Being moved to another
		 * CPU could make the wait longer but we just need to
		 * make sure we waited long enough. Rebalance the
		 * counter for this CPU.
		 */
		if (unlikely(cpu != smp_processor_id())) {
			loops -= (now - bclock);
			cpu = smp_processor_id();
			bclock = mfctl(16);
		}
	}
	preempt_enable();
}