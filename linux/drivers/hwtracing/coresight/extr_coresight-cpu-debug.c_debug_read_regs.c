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
typedef  void* u32 ;
struct debug_drvdata {scalar_t__ edpcsr; scalar_t__ base; void* edvidsr; scalar_t__ edvidsr_present; void* edcidsr; scalar_t__ edcidsr_present; void* edpcsr_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_64BIT ; 
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ EDCIDSR ; 
 scalar_t__ EDPCSR ; 
 scalar_t__ EDPCSR_HI ; 
 scalar_t__ EDPCSR_PROHIBITED ; 
 scalar_t__ EDPRCR ; 
 scalar_t__ EDVIDSR ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_access_permitted (struct debug_drvdata*) ; 
 int /*<<< orphan*/  debug_force_cpu_powered_up (struct debug_drvdata*) ; 
 int /*<<< orphan*/  debug_os_unlock (struct debug_drvdata*) ; 
 void* readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (void*,scalar_t__) ; 

__attribute__((used)) static void debug_read_regs(struct debug_drvdata *drvdata)
{
	u32 save_edprcr;

	CS_UNLOCK(drvdata->base);

	/* Unlock os lock */
	debug_os_unlock(drvdata);

	/* Save EDPRCR register */
	save_edprcr = readl_relaxed(drvdata->base + EDPRCR);

	/*
	 * Ensure CPU power domain is enabled to let registers
	 * are accessiable.
	 */
	debug_force_cpu_powered_up(drvdata);

	if (!debug_access_permitted(drvdata))
		goto out;

	drvdata->edpcsr = readl_relaxed(drvdata->base + EDPCSR);

	/*
	 * As described in ARM DDI 0487A.k, if the processing
	 * element (PE) is in debug state, or sample-based
	 * profiling is prohibited, EDPCSR reads as 0xFFFFFFFF;
	 * EDCIDSR, EDVIDSR and EDPCSR_HI registers also become
	 * UNKNOWN state. So directly bail out for this case.
	 */
	if (drvdata->edpcsr == EDPCSR_PROHIBITED)
		goto out;

	/*
	 * A read of the EDPCSR normally has the side-effect of
	 * indirectly writing to EDCIDSR, EDVIDSR and EDPCSR_HI;
	 * at this point it's safe to read value from them.
	 */
	if (IS_ENABLED(CONFIG_64BIT))
		drvdata->edpcsr_hi = readl_relaxed(drvdata->base + EDPCSR_HI);

	if (drvdata->edcidsr_present)
		drvdata->edcidsr = readl_relaxed(drvdata->base + EDCIDSR);

	if (drvdata->edvidsr_present)
		drvdata->edvidsr = readl_relaxed(drvdata->base + EDVIDSR);

out:
	/* Restore EDPRCR register */
	writel_relaxed(save_edprcr, drvdata->base + EDPRCR);

	CS_LOCK(drvdata->base);
}