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
struct smu_table_context {int /*<<< orphan*/  clocks_table; struct smu_table* tables; } ;
struct smu_table {int /*<<< orphan*/  cpu_addr; } ;
struct smu_context {struct smu_table_context smu_table; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SMU_TABLE_DPMCLOCKS ; 
 int smu_update_table (struct smu_context*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu_v12_0_populate_smc_tables(struct smu_context *smu)
{
	struct smu_table_context *smu_table = &smu->smu_table;
	struct smu_table *table = NULL;

	table = &smu_table->tables[SMU_TABLE_DPMCLOCKS];
	if (!table)
		return -EINVAL;

	if (!table->cpu_addr)
		return -EINVAL;

	return smu_update_table(smu, SMU_TABLE_DPMCLOCKS, 0, smu_table->clocks_table, false);
}