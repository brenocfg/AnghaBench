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
struct smu_table_context {scalar_t__ table_count; int /*<<< orphan*/ * tables; int /*<<< orphan*/ * clocks_table; } ;
struct smu_context {struct smu_table_context smu_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smu_v12_0_fini_smc_tables(struct smu_context *smu)
{
	struct smu_table_context *smu_table = &smu->smu_table;

	if (!smu_table->tables || smu_table->table_count == 0)
		return -EINVAL;

	kfree(smu_table->clocks_table);
	kfree(smu_table->tables);

	smu_table->clocks_table = NULL;
	smu_table->tables = NULL;

	return 0;
}