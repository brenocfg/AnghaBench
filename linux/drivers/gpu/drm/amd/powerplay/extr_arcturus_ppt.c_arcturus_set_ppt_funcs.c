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
struct smu_context {int /*<<< orphan*/ * ppt_funcs; struct smu_table_context smu_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  TABLE_COUNT ; 
 int /*<<< orphan*/  arcturus_ppt_funcs ; 

void arcturus_set_ppt_funcs(struct smu_context *smu)
{
	struct smu_table_context *smu_table = &smu->smu_table;

	smu->ppt_funcs = &arcturus_ppt_funcs;
	smu_table->table_count = TABLE_COUNT;
}