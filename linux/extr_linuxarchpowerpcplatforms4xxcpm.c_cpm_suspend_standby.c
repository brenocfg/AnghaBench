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

/* Variables and functions */
 int /*<<< orphan*/  SPRN_TCR ; 
 unsigned long TCR_DIE ; 
 int /*<<< orphan*/  cpm_idle_sleep (unsigned int) ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void cpm_suspend_standby(unsigned int mask)
{
	unsigned long tcr_save;

	/* disable decrement interrupt */
	tcr_save = mfspr(SPRN_TCR);
	mtspr(SPRN_TCR, tcr_save & ~TCR_DIE);

	/* go to sleep state */
	cpm_idle_sleep(mask);

	/* restore decrement interrupt */
	mtspr(SPRN_TCR, tcr_save);
}