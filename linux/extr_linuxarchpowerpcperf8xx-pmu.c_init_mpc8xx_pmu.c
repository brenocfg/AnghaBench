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
 int /*<<< orphan*/  PERF_TYPE_RAW ; 
 int /*<<< orphan*/  SPRN_CMPA ; 
 int /*<<< orphan*/  SPRN_COUNTA ; 
 int /*<<< orphan*/  SPRN_ICTRL ; 
 int /*<<< orphan*/  mpc8xx_pmu ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int perf_pmu_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_mpc8xx_pmu(void)
{
	mtspr(SPRN_ICTRL, 7);
	mtspr(SPRN_CMPA, 0);
	mtspr(SPRN_COUNTA, 0xffff);

	return perf_pmu_register(&mpc8xx_pmu, "cpu", PERF_TYPE_RAW);
}