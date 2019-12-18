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
struct smu_table_context {int power_play_table_size; void* power_play_table; void* hardcode_pptable; } ;
struct smu_context {struct smu_table_context smu_table; } ;

/* Variables and functions */
 int EINVAL ; 

int smu_sys_get_pp_table(struct smu_context *smu, void **table)
{
	struct smu_table_context *smu_table = &smu->smu_table;

	if (!smu_table->power_play_table && !smu_table->hardcode_pptable)
		return -EINVAL;

	if (smu_table->hardcode_pptable)
		*table = smu_table->hardcode_pptable;
	else
		*table = smu_table->power_play_table;

	return smu_table->power_play_table_size;
}