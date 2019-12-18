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
 int smu_fini_smc_tables (struct smu_context*) ; 

__attribute__((used)) static int smu_smc_table_sw_fini(struct smu_context *smu)
{
	int ret;

	ret = smu_fini_smc_tables(smu);
	if (ret) {
		pr_err("Failed to smu_fini_smc_tables!\n");
		return ret;
	}

	return 0;
}