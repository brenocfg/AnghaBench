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
struct cci_pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCI_PMU_CNTR_CTRL ; 
 int /*<<< orphan*/  pmu_write_register (struct cci_pmu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmu_disable_counter(struct cci_pmu *cci_pmu, int idx)
{
	pmu_write_register(cci_pmu, 0, idx, CCI_PMU_CNTR_CTRL);
}