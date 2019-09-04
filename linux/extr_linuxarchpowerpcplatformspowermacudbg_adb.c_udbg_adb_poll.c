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

__attribute__((used)) static inline void udbg_adb_poll(void)
{
#ifdef CONFIG_ADB_PMU
	if (input_type == input_adb_pmu)
		pmu_poll_adb();
#endif /* CONFIG_ADB_PMU */
#ifdef CONFIG_ADB_CUDA
	if (input_type == input_adb_cuda)
		cuda_poll();
#endif /* CONFIG_ADB_CUDA */
}