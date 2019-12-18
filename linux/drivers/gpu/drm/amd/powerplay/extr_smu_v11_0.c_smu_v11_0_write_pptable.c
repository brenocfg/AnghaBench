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
struct smu_table_context {int /*<<< orphan*/  driver_pptable; } ;
struct smu_context {struct smu_table_context smu_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_TABLE_PPTABLE ; 
 int smu_update_table (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu_v11_0_write_pptable(struct smu_context *smu)
{
	struct smu_table_context *table_context = &smu->smu_table;
	int ret = 0;

	ret = smu_update_table(smu, SMU_TABLE_PPTABLE, 0,
			       table_context->driver_pptable, true);

	return ret;
}