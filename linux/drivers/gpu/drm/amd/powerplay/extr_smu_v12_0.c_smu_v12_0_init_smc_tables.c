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
struct smu_table_context {scalar_t__ table_count; struct smu_table* tables; } ;
struct smu_table {int dummy; } ;
struct smu_context {struct smu_table_context smu_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMU_TABLE_COUNT ; 
 struct smu_table* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int smu_tables_init (struct smu_context*,struct smu_table*) ; 

__attribute__((used)) static int smu_v12_0_init_smc_tables(struct smu_context *smu)
{
	struct smu_table_context *smu_table = &smu->smu_table;
	struct smu_table *tables = NULL;

	if (smu_table->tables || smu_table->table_count == 0)
		return -EINVAL;

	tables = kcalloc(SMU_TABLE_COUNT, sizeof(struct smu_table),
			 GFP_KERNEL);
	if (!tables)
		return -ENOMEM;

	smu_table->tables = tables;

	return smu_tables_init(smu, tables);
}