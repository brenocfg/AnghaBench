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
 unsigned long PMSU_PREPARE_DEEP_IDLE ; 
 int /*<<< orphan*/  SCU_PM_POWEROFF ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  louis ; 
 int /*<<< orphan*/  mvebu_get_scu_base () ; 
 int /*<<< orphan*/  mvebu_v7_pmsu_idle_prepare (unsigned long) ; 
 int /*<<< orphan*/  scu_power_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v7_exit_coherency_flush (int /*<<< orphan*/ ) ; 

int armada_38x_do_cpu_suspend(unsigned long deepidle)
{
	unsigned long flags = 0;

	if (deepidle)
		flags |= PMSU_PREPARE_DEEP_IDLE;

	mvebu_v7_pmsu_idle_prepare(flags);
	/*
	 * Already flushed cache, but do it again as the outer cache
	 * functions dirty the cache with spinlocks
	 */
	v7_exit_coherency_flush(louis);

	scu_power_mode(mvebu_get_scu_base(), SCU_PM_POWEROFF);

	cpu_do_idle();

	return 1;
}