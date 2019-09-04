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
struct TYPE_2__ {unsigned long* pmc_count_mask; unsigned long* pmc_count_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERFMON_CMD_WRITE ; 
 TYPE_1__* alpha_pmu ; 
 int /*<<< orphan*/  wrperfmon (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void alpha_write_pmc(int idx, unsigned long val)
{
	val &= alpha_pmu->pmc_count_mask[idx];
	val <<= alpha_pmu->pmc_count_shift[idx];
	val |= (1<<idx);
	wrperfmon(PERFMON_CMD_WRITE, val);
}