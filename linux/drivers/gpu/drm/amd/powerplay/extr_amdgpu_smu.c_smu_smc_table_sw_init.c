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
struct smu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int smu_init_power (struct smu_context*) ; 
 int smu_init_smc_tables (struct smu_context*) ; 
 int smu_initialize_pptable (struct smu_context*) ; 

__attribute__((used)) static int smu_smc_table_sw_init(struct smu_context *smu)
{
	int ret;

	ret = smu_initialize_pptable(smu);
	if (ret) {
		pr_err("Failed to init smu_initialize_pptable!\n");
		return ret;
	}

	/**
	 * Create smu_table structure, and init smc tables such as
	 * TABLE_PPTABLE, TABLE_WATERMARKS, TABLE_SMU_METRICS, and etc.
	 */
	ret = smu_init_smc_tables(smu);
	if (ret) {
		pr_err("Failed to init smc tables!\n");
		return ret;
	}

	/**
	 * Create smu_power_context structure, and allocate smu_dpm_context and
	 * context size to fill the smu_power_context data.
	 */
	ret = smu_init_power(smu);
	if (ret) {
		pr_err("Failed to init smu_init_power!\n");
		return ret;
	}

	return 0;
}