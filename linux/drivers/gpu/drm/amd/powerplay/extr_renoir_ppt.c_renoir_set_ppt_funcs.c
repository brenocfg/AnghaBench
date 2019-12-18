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
struct smu_table_context {int /*<<< orphan*/  table_count; } ;
struct smu_context {int /*<<< orphan*/  smc_if_version; int /*<<< orphan*/ * ppt_funcs; struct smu_table_context smu_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU12_DRIVER_IF_VERSION ; 
 int /*<<< orphan*/  TABLE_COUNT ; 
 int /*<<< orphan*/  renoir_ppt_funcs ; 

void renoir_set_ppt_funcs(struct smu_context *smu)
{
	struct smu_table_context *smu_table = &smu->smu_table;

	smu->ppt_funcs = &renoir_ppt_funcs;
	smu->smc_if_version = SMU12_DRIVER_IF_VERSION;
	smu_table->table_count = TABLE_COUNT;
}