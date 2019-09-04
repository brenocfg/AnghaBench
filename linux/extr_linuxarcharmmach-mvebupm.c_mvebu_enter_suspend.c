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
 int /*<<< orphan*/  cpu_pm_enter () ; 
 int /*<<< orphan*/  cpu_pm_exit () ; 
 int /*<<< orphan*/  cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_pm_powerdown ; 
 int mvebu_pm_store_bootinfo () ; 
 int /*<<< orphan*/  mvebu_v7_pmsu_idle_exit () ; 
 int /*<<< orphan*/  outer_resume () ; 
 int /*<<< orphan*/  set_cpu_coherent () ; 

__attribute__((used)) static int mvebu_enter_suspend(void)
{
	int ret;

	ret = mvebu_pm_store_bootinfo();
	if (ret)
		return ret;

	cpu_pm_enter();

	cpu_suspend(0, mvebu_pm_powerdown);

	outer_resume();

	mvebu_v7_pmsu_idle_exit();

	set_cpu_coherent();

	cpu_pm_exit();
	return 0;
}