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
typedef  int /*<<< orphan*/  suspend_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  GAFR ; 
 unsigned long GPCR ; 
 int /*<<< orphan*/  GPDR ; 
 unsigned long GPLR ; 
 unsigned long GPSR ; 
 int ICCR ; 
 scalar_t__ ICLR ; 
 scalar_t__ ICMR ; 
 int /*<<< orphan*/  PPAR ; 
 int /*<<< orphan*/  PPDR ; 
 int /*<<< orphan*/  PPSR ; 
 int /*<<< orphan*/  PSDR ; 
 scalar_t__ PSPR ; 
 int /*<<< orphan*/  PSSR ; 
 int /*<<< orphan*/  PSSR_PH ; 
 int RCSR ; 
 int RCSR_HWR ; 
 int RCSR_SMR ; 
 int RCSR_SWR ; 
 int RCSR_WDR ; 
 int /*<<< orphan*/  RESTORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAVE (int /*<<< orphan*/ ) ; 
 int SLEEP_SAVE_COUNT ; 
 int /*<<< orphan*/  Ser1SDCR0 ; 
 scalar_t__ __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_resume ; 
 int /*<<< orphan*/  cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1100_finish_suspend ; 

__attribute__((used)) static int sa11x0_pm_enter(suspend_state_t state)
{
	unsigned long gpio, sleep_save[SLEEP_SAVE_COUNT];

	gpio = GPLR;

	/* save vital registers */
	SAVE(GPDR);
	SAVE(GAFR);

	SAVE(PPDR);
	SAVE(PPSR);
	SAVE(PPAR);
	SAVE(PSDR);

	SAVE(Ser1SDCR0);

	/* Clear previous reset status */
	RCSR = RCSR_HWR | RCSR_SWR | RCSR_WDR | RCSR_SMR;

	/* set resume return address */
	PSPR = __pa_symbol(cpu_resume);

	/* go zzz */
	cpu_suspend(0, sa1100_finish_suspend);

	/*
	 * Ensure not to come back here if it wasn't intended
	 */
	RCSR = RCSR_SMR;
	PSPR = 0;

	/*
	 * Ensure interrupt sources are disabled; we will re-init
	 * the interrupt subsystem via the device manager.
	 */
	ICLR = 0;
	ICCR = 1;
	ICMR = 0;

	/* restore registers */
	RESTORE(GPDR);
	RESTORE(GAFR);

	RESTORE(PPDR);
	RESTORE(PPSR);
	RESTORE(PPAR);
	RESTORE(PSDR);

	RESTORE(Ser1SDCR0);

	GPSR = gpio;
	GPCR = ~gpio;

	/*
	 * Clear the peripheral sleep-hold bit.
	 */
	PSSR = PSSR_PH;

	return 0;
}