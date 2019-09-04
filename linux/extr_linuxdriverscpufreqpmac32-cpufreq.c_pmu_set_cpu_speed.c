#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct adb_request {int /*<<< orphan*/  complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  active_mm; } ;

/* Variables and functions */
 unsigned long L2CR_L2E ; 
 unsigned long L3CR_L3E ; 
 int /*<<< orphan*/  PMAC_FTR_SLEEP_STATE ; 
 int /*<<< orphan*/  PMU_CPU_SPEED ; 
 unsigned long _get_L2CR () ; 
 unsigned long _get_L3CR () ; 
 int /*<<< orphan*/  _set_L2CR (unsigned long) ; 
 int /*<<< orphan*/  _set_L3CR (unsigned long) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  enable_kernel_fp () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  low_sleep_handler () ; 
 int /*<<< orphan*/  mb () ; 
 unsigned int mpic_cpu_get_priority () ; 
 int /*<<< orphan*/  mpic_cpu_set_priority (unsigned int) ; 
 int /*<<< orphan*/  pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pmu_poll () ; 
 int /*<<< orphan*/  pmu_request (struct adb_request*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char,char,char,float,int) ; 
 int /*<<< orphan*/  pmu_resume () ; 
 int /*<<< orphan*/  pmu_suspend () ; 
 int /*<<< orphan*/  pmu_unlock () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  set_dec (int) ; 
 int /*<<< orphan*/  switch_mmu_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmu_set_cpu_speed(int low_speed)
{
	struct adb_request req;
	unsigned long save_l2cr;
	unsigned long save_l3cr;
	unsigned int pic_prio;
	unsigned long flags;

	preempt_disable();

#ifdef DEBUG_FREQ
	printk(KERN_DEBUG "HID1, before: %x\n", mfspr(SPRN_HID1));
#endif
	pmu_suspend();

	/* Disable all interrupt sources on openpic */
 	pic_prio = mpic_cpu_get_priority();
	mpic_cpu_set_priority(0xf);

	/* Make sure the decrementer won't interrupt us */
	asm volatile("mtdec %0" : : "r" (0x7fffffff));
	/* Make sure any pending DEC interrupt occurring while we did
	 * the above didn't re-enable the DEC */
	mb();
	asm volatile("mtdec %0" : : "r" (0x7fffffff));

	/* We can now disable MSR_EE */
	local_irq_save(flags);

	/* Giveup the FPU & vec */
	enable_kernel_fp();

#ifdef CONFIG_ALTIVEC
	if (cpu_has_feature(CPU_FTR_ALTIVEC))
		enable_kernel_altivec();
#endif /* CONFIG_ALTIVEC */

	/* Save & disable L2 and L3 caches */
	save_l3cr = _get_L3CR();	/* (returns -1 if not available) */
	save_l2cr = _get_L2CR();	/* (returns -1 if not available) */

	/* Send the new speed command. My assumption is that this command
	 * will cause PLL_CFG[0..3] to be changed next time CPU goes to sleep
	 */
	pmu_request(&req, NULL, 6, PMU_CPU_SPEED, 'W', 'O', 'O', 'F', low_speed);
	while (!req.complete)
		pmu_poll();

	/* Prepare the northbridge for the speed transition */
	pmac_call_feature(PMAC_FTR_SLEEP_STATE,NULL,1,1);

	/* Call low level code to backup CPU state and recover from
	 * hardware reset
	 */
	low_sleep_handler();

	/* Restore the northbridge */
	pmac_call_feature(PMAC_FTR_SLEEP_STATE,NULL,1,0);

	/* Restore L2 cache */
	if (save_l2cr != 0xffffffff && (save_l2cr & L2CR_L2E) != 0)
 		_set_L2CR(save_l2cr);
	/* Restore L3 cache */
	if (save_l3cr != 0xffffffff && (save_l3cr & L3CR_L3E) != 0)
 		_set_L3CR(save_l3cr);

	/* Restore userland MMU context */
	switch_mmu_context(NULL, current->active_mm, NULL);

#ifdef DEBUG_FREQ
	printk(KERN_DEBUG "HID1, after: %x\n", mfspr(SPRN_HID1));
#endif

	/* Restore low level PMU operations */
	pmu_unlock();

	/*
	 * Restore decrementer; we'll take a decrementer interrupt
	 * as soon as interrupts are re-enabled and the generic
	 * clockevents code will reprogram it with the right value.
	 */
	set_dec(1);

	/* Restore interrupts */
 	mpic_cpu_set_priority(pic_prio);

	/* Let interrupts flow again ... */
	local_irq_restore(flags);

#ifdef DEBUG_FREQ
	debug_calc_bogomips();
#endif

	pmu_resume();

	preempt_enable();

	return 0;
}