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
 unsigned int XCHAL_NUM_PERF_COUNTERS ; 
 int /*<<< orphan*/  XTENSA_PMU_PMCTRL (unsigned int) ; 
 int /*<<< orphan*/  XTENSA_PMU_PMG ; 
 int /*<<< orphan*/  XTENSA_PMU_PMSTAT (unsigned int) ; 
 int /*<<< orphan*/  get_er (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_er (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xtensa_pmu_setup(int cpu)
{
	unsigned i;

	set_er(0, XTENSA_PMU_PMG);
	for (i = 0; i < XCHAL_NUM_PERF_COUNTERS; ++i) {
		set_er(0, XTENSA_PMU_PMCTRL(i));
		set_er(get_er(XTENSA_PMU_PMSTAT(i)), XTENSA_PMU_PMSTAT(i));
	}
	return 0;
}